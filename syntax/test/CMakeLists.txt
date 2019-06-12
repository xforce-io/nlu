cmake_minimum_required(VERSION 2.6.4)

project(syntax)

include_directories(
  /usr/local/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/../deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/../deps/basic/include/
  ${CMAKE_SOURCE_DIR}/../deps/milkie/include/
  ${CMAKE_SOURCE_DIR}/../deps/ner/include/
  ${CMAKE_SOURCE_DIR}/../deps/segmentor/include/
  ${CMAKE_SOURCE_DIR}/../deps/pos_tagging/include/
  ${CMAKE_SOURCE_DIR}/../deps/chunk/include/
  ../3rd/lua-5.3.5/include
)

link_directories(
  /usr/local/lib/
  /usr/local/lib64/
  /home/freeman/software/lib/
  /home/freeman/dev/github/xforce-io/nlu/milkie/3rd/lua-5.3.5/lib
)

FILE(GLOB_RECURSE LOCAL_CPP_FILES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -Wno-sign-compare -ansi -pthread -std=c++11 -DUT_TEST -DUNICODE=1 -pg")
set(LIB_DEPS
  ${CMAKE_SOURCE_DIR}/../deps/chunker/lib/chunker/libchunker.a
  ${CMAKE_SOURCE_DIR}/../deps/pos_tagging/lib/pos_tagging/libpos_tagging.a
  ${CMAKE_SOURCE_DIR}/../deps/segmentor/lib/segmentor/libsegmentor.a
  ${CMAKE_SOURCE_DIR}/../deps/ner/lib/ner/libner.a
  ${CMAKE_SOURCE_DIR}/../deps/milkie/lib/milkie/libmilkie.a
  ${CMAKE_SOURCE_DIR}/../deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/../deps/public-cpp/lib/public-cpp/libpublic-cpp.a
)

find_library(LUA_LIBRARY lua ../3rd/lua-5.3.5/lib NO_DEFAULT_PATH)

link_libraries(
  ${LIB_DEPS}
  lua
  log4cplusU
  gtest
  pthread
  z
  curl
  dl
)

add_executable(testMatcher
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/model/test_matcher.cpp
)
