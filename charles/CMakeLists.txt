cmake_minimum_required(VERSION 2.6.4)

project(charles)

include_directories(
  /usr/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/milkie/include/
  ${CMAKE_SOURCE_DIR}/deps/ner/include/
  ${CMAKE_SOURCE_DIR}/deps/segmentor/include/
  ${CMAKE_SOURCE_DIR}/deps/pos_tagging/include/
  ${CMAKE_SOURCE_DIR}/deps/chunker/include/
  ${CMAKE_SOURCE_DIR}/deps/syntax/include/
)

link_directories(
  /home/freeman/software/lib/
  /home/freeman/dev/github/xforce-io/nlu/milkie/3rd/lua-5.3.5/lib
)

set(CMAKE_CXX_COMPILER g++)

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/syntax/lib/syntax/libsyntax.a
  ${CMAKE_SOURCE_DIR}/deps/chunker/lib/chunker/libchunker.a
  ${CMAKE_SOURCE_DIR}/deps/pos_tagging/lib/pos_tagging/libpos_tagging.a
  ${CMAKE_SOURCE_DIR}/deps/segmentor/lib/segmentor/libsegmentor.a
  ${CMAKE_SOURCE_DIR}/deps/ner/lib/ner/libner.a
  ${CMAKE_SOURCE_DIR}/deps/milkie/lib/milkie/libmilkie.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
)

add_executable(charles
  ${SEG_FILES} src/charles.h src/details/charles.cpp src/model/analysis/split/rule.h src/model/analysis/split/rule_pos_tag.h src/model/analysis/split/details/rule_pos_tag.cpp src/model/analysis/split/rule_syntax_rule.h src/model/analysis/split/details/rule_syntax_rule.cpp src/model/analysis/split/split_rule_mgr.h src/model/analysis/split/details/split_rule_mgr.cpp src/model/analysis/split/split_stage.h src/model/analysis/split/details/split_stage.cpp src/model/analysis/split/rule_syntax_prep.h src/model/analysis/split/details/rule_syntax_prep.cpp src/model/analysis/split/details/rule.cpp src/model/analysis/split/rule_syntax_cont_np.h src/model/analysis/split/details/rule_syntax_cont_np.cpp src/model/analysis/split/forbid_item.h src/model/analysis/split/forbid_mgr.h src/model/analysis/split/details/forbid_mgr.cpp src/model/analysis/split/rule_syntax_verb_arg.h src/model/analysis/split/details/rule_syntax_verb_arg.cpp src/model/analysis/sub_branch.h src/model/analysis/details/sub_branch.cpp src/model/analysis/split/rule_syntax_arg.h src/model/analysis/split/details/rule_syntax_arg.cpp src/model/analysis/split/rule_syntax_rp_arg.h src/model/analysis/split/details/rule_syntax_rp_arg.cpp src/model/analysis/end_tags.h src/model/analysis/details/end_tags.cpp)

target_link_libraries(charles
  ${LIB_DEPS}
  lua
  log4cplusU
  pthread
  rt
  z
  dl
  )
