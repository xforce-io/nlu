cmake_minimum_required(VERSION 2.6.4)

project(segmentor)

include_directories(
  /usr/local/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/../deps/public-cpp/include/
)

link_directories(
  /usr/local/lib/
  /usr/local/lib64/
  /home/freeman/software/lib/
)

FILE(GLOB_RECURSE LOCAL_CPP_FILES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -pthread -std=c++11 -DUT_TEST -Dprivate=public")

link_libraries(
  log4cplus
  gtest
  pthread
  z
  curl
)

add_executable(testBigramDict
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/data/test_bigram_dict.cpp
)
