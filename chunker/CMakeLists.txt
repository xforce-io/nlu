cmake_minimum_required(VERSION 2.6.4)

project(chunker)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/milkie/include/
)

link_directories(
)

set(CMAKE_CXX_COMPILER g++)

set(SEGMENTOR_OUTPUT_PATH chunker/)
set(SEGMENTOR_LIB_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/lib/chunker)
set(SEGMENTOR_INC_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/include/chunker)
set(SEGMENTOR_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

add_library(chunker
  ${SEG_FILES})

target_link_libraries(chunker
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET chunker
  PRE_BUILD

  #make chunker
  COMMAND mkdir -p ${SEGMENTOR_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}/public/

  COMMAND cp ${SEGMENTOR_SRC_DIR}/chunker.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/dep.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${SEGMENTOR_OUTPUT_PATH}/version
)

add_custom_command(TARGET chunker
  POST_BUILD

  #make chunker
  COMMAND cp libchunker.a ${SEGMENTOR_LIB_OUTPUT_PATH}
)
