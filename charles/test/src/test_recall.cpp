#include <locale>

#include "gtest/gtest.h"

#include "../../../src/charles.h"
#include "../../../src/model/base_modules.h"
#include "../../../src/model/analysis/analysis_clause.h"

LOGGER_IMPL(xforce::xforce_logger, L"syntax")

using namespace xforce;
using namespace xforce::nlu;
using namespace xforce::nlu::charles;

std::string caseName;

int main(int argc, char **argv) {
  if (argc > 1) {
    caseName = std::string(argv[1]);
    std::cout << caseName << std::endl;
  }
  
  setlocale(LC_ALL, "");
  LOGGER_SYS_INIT(L"../conf/log.conf");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(testAll, all) {
  const xforce::JsonType* conf = xforce::JsonType::CreateConf("../conf/charles.conf");
  ASSERT_TRUE(Charles::Init(*conf));

  std::vector<std::string> filepaths;
  if (caseName.empty()) {
    xforce::IOHelper::ScanFiles("../data/recall", filepaths);
    ASSERT_TRUE(filepaths.size() > 0);
  } else {
    filepaths.push_back("../data/recall/" + caseName);
  }

  std::vector<std::string> lines;
  xforce::Timer timer;
  for (auto &filepath : filepaths) {
    lines.clear();
    ASSERT_TRUE(xforce::IOHelper::ReadLinesFromFilepath(filepath, lines));

    for (auto &line : lines) {
      std::string lineAfterTrim = xforce::StrHelper::Trim(line);
      if (lineAfterTrim.empty() || lineAfterTrim[0] == '#') {
        continue;
      }

      auto query = xforce::StrHelper::Str2Wstr(lineAfterTrim);
      AnalysisClause analysisClause(*query, basic::CollectionSyntaxTag(true));
      ASSERT_TRUE(analysisClause.Init());

      timer.Start(true);
      analysisClause.Process();
      timer.Stop(true);
      std::cout << lineAfterTrim << "\tcost[" << timer.TimeMs() << "]" << std::endl;
      assert(analysisClause.GetResults().size() >= 1);

    }
  }
}
