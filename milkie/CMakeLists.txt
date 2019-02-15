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

FILE(GLOB_RECURSE MILKIE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -DUNICODE -Wno-sign-compare")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

find_library(LUA_LIBRARY lua ./3rd/lua-5.3.5/lib NO_DEFAULT_PATH)

add_library(milkie
  ${MILKIE_FILES} src/core/model/context/storage_key.h src/core/model/pattern_item/details/pattern_item_reg.cpp src/core/model/pattern_item/pattern_item_reg.h)

target_link_libraries(milkie
  ${LIB_DEPS}
  ${LUA_LIBRARY}
  log4cplus
  pthread
  rt
  z
  )
