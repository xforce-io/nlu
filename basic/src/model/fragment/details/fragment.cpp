#include "../fragment.h"

namespace xforce { namespace nlu { namespace basic {

Fragment::~Fragment() {
  if (nullptr != str_) {
    XFC_DELETE(str_)
  }
}

bool Fragment::Same(const Fragment &other) const {
  return offset_ == other.offset_ && len_ == other.len_;
}

void Fragment::Dump(JsonType &jsonType) const {
  jsonType["offset"] = offset_;
  jsonType["len"] = len_;
  jsonType["conf"] = confidence_.GetScore();
  jsonType["strategy"] = (size_t)strategy_;
}

const std::string& Fragment::StrCategory(typename Fragment::Category category) {
  static const std::string kStrSegment = "segment";
  static const std::string kStrChunk = "chunk";
  static const std::string kStrChunkSep = "chunkSep";
  static const std::string kStrNameEntity = "nameEntity";
  static const std::string kStrSemantic = "semantic";
  static const std::string kStrUndef = "undef";
  switch (category) {
    case kSegment :
      return kStrSegment;
    case kChunk :
      return kStrChunk;   
    case kChunkSep :
      return kStrChunkSep; 
    case kNameEntity :    
      return kStrNameEntity;  
    case kSemantic :
      return kStrSemantic;  
    default :
      return kStrUndef;  
  }
}


}}}
