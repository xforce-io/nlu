cmake_minimum_required(VERSION 2.6.4)

project(segmentor)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
)

link_directories(
)

set(SEG_OUTPUT_PATH segmentor/)
set(SEG_LIB_OUTPUT_PATH  ${SEG_OUTPUT_PATH}/lib/segmentor)
set(SEG_INC_OUTPUT_PATH  ${SEG_OUTPUT_PATH}/include/)
set(SEG_INC_OUTPUT_PATH_MAGNETO  ${SEG_INC_OUTPUT_PATH}/segmentor/)
set(SEG_INC_OUTPUT_PATH_PUBLIC_CPP  ${SEG_INC_OUTPUT_PATH}/deps/public-cpp/include/public-cpp/)

set(SEG_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")
set(SEG_SRC_DIR_PUBLIC_CPP "${CMAKE_SOURCE_DIR}/deps/public-cpp/include/public-cpp/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -O2 -std=c++11")
set(LIB_DEPS ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a)

add_executable(segmentor
  ${SEG_FILES})

target_link_libraries(segmentor
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )
