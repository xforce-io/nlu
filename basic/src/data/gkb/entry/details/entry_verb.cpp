#include "../entry_verb.h"

namespace xforce { namespace nlu { namespace basic {

EntryVerb::EntryVerb() :
    zhu_(false),
    argTi_(false),
    argWei_(false),
    argZhun_(false),
    doubleArgs_(false),
    dongjie_(false),
    dongqu_(false) {}

int EntryVerb::Parse(const std::vector<std::wstring> &items) {
  int ret = Entry::Parse(items);
  if (ret!=0) {
    return ret;
  }

  zhu_ = !items[kColZhu].empty();

  if (items[kColTiWeiZhun].find(L'体') != std::wstring::npos) {
    argTi_ = true;
  }

  if (items[kColTiWeiZhun].find(L'谓') != std::wstring::npos) {
    argWei_ = true;
  }

  if (items[kColTiWeiZhun].find(L'准') != std::wstring::npos) {
    argZhun_ = true;
  }

  doubleArgs_ = !items[kColDoubleArgs].empty();

  dongjie_ = !items[kColDongjie].empty();
  dongqu_ = !items[kColDongqu].empty();
  return 0;
}

}}}
