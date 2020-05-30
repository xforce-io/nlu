#pragma once

#include "fragment_set.hpp"
#include "segment.h"
#include "name_entity.h"
#include "chunk_sep.h"
#include "chunk.h"

namespace xforce { namespace nlu { namespace basic {

class ManagerFragmentSet {
 public:
  ManagerFragmentSet(const std::wstring &query);

  template <typename FragmentType>
  void Set(const typename FragmentType::Set &set);

  ManagerFragmentSet* Build(size_t from, size_t to);
  ManagerFragmentSet* Clone();

  template <typename FragmentType>
  const typename FragmentType::Set& Get() const;

  template <typename FragmentType>
  typename FragmentType::Set& Get();

  void Dump(
          JsonType &jsonType,
          const ManagerFragmentSet *managerFragmentSet) const;

 private:
  const std::wstring query_;
  typename NameEntity::Set nameEntities_;
  typename Segment::Set segments_;
  typename ChunkSep::Set chunkSeps_;
  typename Chunk::Set chunks_;
};

template <>
void ManagerFragmentSet::Set<NameEntity>(const typename NameEntity::Set &set) {
  nameEntities_ = set;
}

template <>
void ManagerFragmentSet::Set<Segment>(const typename Segment::Set &set) {
  segments_ = set;
}

template <>
void ManagerFragmentSet::Set<ChunkSep>(const typename ChunkSep::Set &set) {
  chunkSeps_ = set;
}

template <>
void ManagerFragmentSet::Set<Chunk>(const typename Chunk::Set &set) {
  chunks_ = set;
}

template <>
const typename NameEntity::Set& ManagerFragmentSet::Get<NameEntity>() const {
  return nameEntities_;
}

template <>
typename NameEntity::Set& ManagerFragmentSet::Get<NameEntity>() {
  return nameEntities_;
}

template <>
const typename Segment::Set& ManagerFragmentSet::Get<Segment>() const {
  return segments_;
}

template <>
typename Segment::Set& ManagerFragmentSet::Get<Segment>() {
  return segments_;
}

template <>
const typename ChunkSep::Set& ManagerFragmentSet::Get<ChunkSep>() const {
  return chunkSeps_;
}

template <>
typename ChunkSep::Set& ManagerFragmentSet::Get<ChunkSep>() {
  return chunkSeps_;
}

template <>
const typename Chunk::Set& ManagerFragmentSet::Get<Chunk>() const {
  return chunks_;
}

template <>
typename Chunk::Set& ManagerFragmentSet::Get<Chunk>() {
  return chunks_;
}

}}}
