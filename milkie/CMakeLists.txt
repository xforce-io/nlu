cmake_minimum_required(VERSION 2.6.4)

project(milkie)

set(LUA_INCLUDE_DIRS ./3rd/lua-5.3.5/include)
include_directories(
  /usr/include/
  ${LUA_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
)

link_directories(
)

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -DUNICODE -Wno-sign-compare")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

find_library(LUA_LIBRARY lua ./3rd/lua-5.3.5/lib NO_DEFAULT_PATH)

add_library(milkie
  ${SEG_FILES} src/core/model/codeseg/code_seg.h src/core/model/codeseg/details/code_seg.cpp src/core/model/context/storage.h test/src/model/pattern_item/test_pattern_item_repr.cpp)

target_link_libraries(milkie
  ${LIB_DEPS}
  ${LUA_LIBRARY}
  log4cplus
  pthread
  rt
  z
  )
