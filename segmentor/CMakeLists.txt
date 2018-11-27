cmake_minimum_required(VERSION 2.6.4)

project(segmentor)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/segmentor/include/
  ${CMAKE_SOURCE_DIR}/deps/ner/include/
)

link_directories(
)

set(SEGMENTOR_OUTPUT_PATH segmentor/)
set(SEGMENTOR_LIB_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/lib/segmentor)
set(SEGMENTOR_INC_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/include/segmentor)
set(SEGMENTOR_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -O2")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/ner/lib/ner/libner.a
)

add_library(segmentor
  ${SEG_FILES})

target_link_libraries(segmentor
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET segmentor
  PRE_BUILD

  #make segmentor
  COMMAND mkdir -p ${SEGMENTOR_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}/public/

  COMMAND cp ${SEGMENTOR_SRC_DIR}/segmentor.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/constant.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/dep.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${SEGMENTOR_OUTPUT_PATH}/version
)

add_custom_command(TARGET segmentor
  POST_BUILD

  #make segmentor
  COMMAND cp libsegmentor.a ${SEGMENTOR_LIB_OUTPUT_PATH}
)
