cmake_minimum_required(VERSION 2.6.4)

project(charles)

include_directories(
  /usr/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/ner/include/
  ${CMAKE_SOURCE_DIR}/deps/segmentor/include/
  ${CMAKE_SOURCE_DIR}/deps/pos_tagging/include/
  ${CMAKE_SOURCE_DIR}/deps/chunker/include/
  ${CMAKE_SOURCE_DIR}/deps/syntax/include/
)

link_directories(
  /home/freeman/software/lib/
)

set(CMAKE_CXX_COMPILER g++)

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/pos_tagging/lib/pos_tagging/libpos_tagging.a
  ${CMAKE_SOURCE_DIR}/deps/segmentor/lib/segmentor/libsegmentor.a
  ${CMAKE_SOURCE_DIR}/deps/ner/lib/ner/libner.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
)

add_executable(charles
  ${SEG_FILES})

target_link_libraries(charles
  ${LIB_DEPS}
  log4cplusU
  pthread
  rt
  z
  )
