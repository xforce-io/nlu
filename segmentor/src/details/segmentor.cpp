#include "../segmentor.h"
#include "../conf/conf.h"
#include "../data/manager.h"
#include "../model/graph/graph.h"
#include "../model/graph/trigger/manager_triggers.h"
#include "ner/ner.h"
#include "basic/data/manager.h"
#include "basic/data/gkb/gkb.h"

namespace xforce { namespace nlu { namespace segmentor {

bool Segmentor::Init(
    const xforce::JsonType &confSeg,
    const xforce::JsonType &confNer) {
  bool ret = xforce::nlu::ner::Ner::Init(confNer);
  if (!ret) {
    return false;
  }

  ret = Conf::Get().Init(confSeg);
  if (!ret) {
    FATAL("fail_init_conf[segmentor]");
    return false;
  }

  ret = Manager::Get().Init();
  if (!ret) {
    FATAL("fail_init_data_manager[segmentor]");
    return false;
  }
  return true;
}

void Segmentor::Parse(
    const std::wstring &query, 
    basic::FragmentSet<basic::Segment> &segments,
    basic::FragmentSet<basic::NameEntity> &nameEntities) {
  Graph *graph = new Graph(query);
  graph->Process(segments, nameEntities);
  XFC_DELETE(graph)
  Segmentor::PostProcess_(query, segments);
}

void Segmentor::Tini() {
  ManagerTriggers::Tini();  
  Manager::Tini();  
  Conf::Tini();
}

void Segmentor::PostProcess_(
        const std::wstring &query,
        basic::FragmentSet<basic::Segment> &segments) {
  auto &segs = segments.GetAll();
  auto cur = segs.begin();
  if (cur == segs.end()) {
    return;
  }

  while (true) {
    auto next = cur;
    ++next;
    if (next == segs.end()) {
      return;
    }

    if ((*cur)->GetPosTag() == basic::PosTag::Type::kV &&
        (*next)->GetPosTag() == basic::PosTag::Type::kV) {
      bool ret = basic::Manager::Get().GetGkb().IsPhrase(
              (*cur)->GetStrFromSentence(query),
              (*next)->GetStrFromSentence(query));
      if (ret) {
        basic::Segment newSegment(
                basic::PosTag::Type::kV,
                (*cur)->GetOffset(),
                (*cur)->GetLen() + (*next)->GetLen());
        segments.Erase(cur);
        segments.Erase(next);
        segments.Add(newSegment);
      }
    }
    cur = next;
  }
}

}}}
