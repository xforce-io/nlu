
PatternSet::PatternSet(const StructPatternSet &structPatternSet) {
  patternStrsTrie_ = BuildPatternStrsTrie_();
}
