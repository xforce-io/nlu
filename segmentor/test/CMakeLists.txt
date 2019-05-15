cmake_minimum_required(VERSION 2.6.4)

project(segmentor)

include_directories(
  /usr/local/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/../deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/../deps/basic/include/
  ${CMAKE_SOURCE_DIR}/../deps/ner/include/
)

link_directories(
  /usr/local/lib/
  /usr/local/lib64/
  /home/freeman/software/lib/
)

FILE(GLOB_RECURSE LOCAL_CPP_FILES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -pthread -std=c++11 -DUT_TEST -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/../deps/ner/lib/ner/libner.a
  ${CMAKE_SOURCE_DIR}/../deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/../deps/public-cpp/lib/public-cpp/libpublic-cpp.a
)

link_libraries(
  ${LIB_DEPS}
  log4cplusU
  gtest
  pthread
  z
  curl
)

add_executable(testSurname
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/data/test_surname.cpp
)

add_executable(testBigramDict
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/data/test_bigram_dict.cpp
)

add_executable(testWordDict
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/data/test_word_dict.cpp
)

add_executable(testRegression
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/test_regression.cpp
)

add_executable(testCase
  ${LOCAL_CPP_FILES}
  ${CMAKE_SOURCE_DIR}/src/test_case.cpp
)
