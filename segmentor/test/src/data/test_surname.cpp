#include "gtest/gtest.h"
#include "../../../src/data/surname.h"

LOGGER_IMPL(xforce::xforce_logger, L"segmentor")

using namespace xforce::nlu::segmentor;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_all, all) {
  setlocale(LC_ALL, "");

  Surname *surname = new Surname();
  ASSERT_TRUE(surname->Init("../../data/surname.dic"));
  ASSERT_TRUE(surname->StartWithSurname(L"管理员", 0) > 0);
  ASSERT_TRUE(surname->StartWithSurname(L"员管理", 0) < 0);
}
