#pragma once

#include "../../public.h"
#include "../pos/pos_tag.h"
#include "../syntax/syntax_tag.h"
#include "fragment.h"
#include "fragment_set.hpp"
#include "fragment_multitag.hpp"
#include "segment.h"

namespace xforce { namespace nlu { namespace basic {

class NluContext;
class SemanticUnit;

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

  inline void SetDescDir(DescDir descDir);
  inline DescDir GetDescDir() const;

  inline void SetSemanticUnit(const std::shared_ptr<SemanticUnit> &semanticUnit);
  inline const std::shared_ptr<SemanticUnit>& GetSemanticUnit() const;
  inline std::shared_ptr<SemanticUnit>& GetSemanticUnit();

  Fragment::Category GetCategory() const { return kChunk; }

  std::shared_ptr<Segment> FindSeg(
          const NluContext &nluContext,
          basic::PosTag::Type::Val posTag);

  virtual void Dump(JsonType &jsonType) const;

 private:
  static void AddTagForCtx(
          const NluContext &nluContext,
          Chunk &chunk,
          SyntaxTag::Type::Val tag);
 private:
  DescDir descDir_;

  bool verbArgInfo_;
  bool isArgTi_;
  bool isArgWei_;
  bool isArgZhun_;
  bool isDoubleArgs_;

  std::shared_ptr<SemanticUnit> semanticUnit_;
};

Chunk::Chunk() :
  Super(),
  verbArgInfo_(false) {}

Chunk::Chunk(
        const NluContext &nluContext,
        SyntaxTag::Type::Val syntaxTag,
        size_t offset,
        size_t len,
        uint32_t strategy) :
    Super(syntaxTag, offset, len, strategy),
    verbArgInfo_(false) {
  AddTagForCtx(nluContext, *this, syntaxTag);
}

Chunk::Chunk(const Chunk &other) :
    Super(SCAST<const Super&>(other)),
    descDir_(other.descDir_),
    verbArgInfo_(other.verbArgInfo_),
    isArgTi_(other.isArgTi_),
    isArgWei_(other.isArgWei_),
    isArgZhun_(other.isArgZhun_),
    isDoubleArgs_(other.isDoubleArgs_) {}

void Chunk::SetDescDir(DescDir descDir) {
  descDir_ = descDir;
}

Chunk::DescDir Chunk::GetDescDir() const {
  return descDir_;
}

void Chunk::SetSemanticUnit(const std::shared_ptr<SemanticUnit> &semanticUnit) {
  semanticUnit_ = semanticUnit;
}

const std::shared_ptr<SemanticUnit>& Chunk::GetSemanticUnit() const {
  return semanticUnit_;
}

std::shared_ptr<SemanticUnit>& Chunk::GetSemanticUnit() {
  return semanticUnit_;
}

}}}
