cmake_minimum_required(VERSION 2.6.4)

project(charles)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/ner/include/
)

link_directories(
)

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -O2")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/ner/lib/ner/libner.a
)

add_executable(charles
  ${SEG_FILES})

target_link_libraries(charles
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )
