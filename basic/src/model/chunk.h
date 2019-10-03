#pragma once

#include "../public.h"
#include "pos/pos_tag.h"
#include "syntax/syntax_tag.h"
#include "fragment/fragment.h"
#include "fragment/fragment_set.hpp"
#include "fragment/fragment_multitag.hpp"
#include "segment.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext;

class Chunk : public FragmentMultitag<SyntaxTag::Type> {
 public:
  enum DescDir {
    kNone,
    kLeft,
    kRight,
    kBoth,
  };

 public:
  typedef FragmentMultitag<SyntaxTag::Type> Super;
  typedef FragmentSet<Chunk> Set;

 public:
  inline Chunk();
  inline Chunk(
          const NluContext &nluContext,
          SyntaxTag::Type::Val syntaxTag,
          size_t offset,
          size_t len,
          uint32_t strategy=0);

  inline Chunk(const Chunk &other);
  virtual ~Chunk() {}

  inline void SetNeedToVerify(bool needToVerify);
  inline void SetDescDir(DescDir descDir);

  bool GetNeedToVerify() const { return needToVerify_; }
  inline DescDir GetDescDir() const;

  virtual const std::string& GetCategory() const;

  virtual void Dump(JsonType &jsonType);

 private:
  std::shared_ptr<Segment> FindSeg_(
          const NluContext &nluContext,
          basic::PosTag::Type::Val posTag);

 private:
  static void AddTagForCtx(
          const NluContext &nluContext,
          Chunk &chunk,
          SyntaxTag::Type::Val tag);
 private:
  bool needToVerify_;

  DescDir descDir_;

  bool verbArgInfo_;
  bool isArgTi_;
  bool isArgWei_;
  bool isArgZhun_;
  bool isDoubleArgs_;
};

Chunk::Chunk() :
  Super(),
  needToVerify_(false),
  verbArgInfo_(false) {}

Chunk::Chunk(
        const NluContext &nluContext,
        SyntaxTag::Type::Val syntaxTag,
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Super(syntaxTag, offset, len, strategy),
    needToVerify_(false),
    verbArgInfo_(false) {
  AddTagForCtx(nluContext, *this, syntaxTag);
}

Chunk::Chunk(const Chunk &other) :
    Super(SCAST<const Super&>(other)),
    needToVerify_(other.needToVerify_),
    descDir_(other.descDir_),
    verbArgInfo_(other.verbArgInfo_),
    isArgTi_(other.isArgTi_),
    isArgWei_(other.isArgWei_),
    isArgZhun_(other.isArgZhun_),
    isDoubleArgs_(other.isDoubleArgs_) {}

void Chunk::SetNeedToVerify(bool needToVerify) {
  needToVerify_ = needToVerify;
}

void Chunk::SetDescDir(DescDir descDir) {
  descDir_ = descDir;
}

Chunk::DescDir Chunk::GetDescDir() const {
  return descDir_;
}

}}}
