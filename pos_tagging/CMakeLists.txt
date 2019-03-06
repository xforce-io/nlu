cmake_minimum_required(VERSION 2.6.4)

project(pos_tagging)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/segmentor/include/
)

link_directories(
)

set(SEGMENTOR_OUTPUT_PATH pos_tagging/)
set(SEGMENTOR_LIB_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/lib/pos_tagging)
set(SEGMENTOR_INC_OUTPUT_PATH  ${SEGMENTOR_OUTPUT_PATH}/include/pos_tagging)
set(SEGMENTOR_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -O2")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/deps/segmentor/lib/segmentor/libsegmentor.a
)

add_library(pos_tagging
  ${SEG_FILES} src/data/gkb_zk.h src/data/details/gkb_zk.cpp src/data/manager.h src/data/details/manager.cpp)

target_link_libraries(pos_tagging
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET pos_tagging
  PRE_BUILD

  #make pos_tagging
  COMMAND mkdir -p ${SEGMENTOR_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${SEGMENTOR_INC_OUTPUT_PATH}/public/

  COMMAND cp ${SEGMENTOR_SRC_DIR}/pos_tagging.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/public.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND cp ${SEGMENTOR_SRC_DIR}/public/dep.h ${SEGMENTOR_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${SEGMENTOR_OUTPUT_PATH}/version
)

add_custom_command(TARGET pos_tagging
  POST_BUILD

  #make pos_tagging
  COMMAND cp libpos_tagging.a ${SEGMENTOR_LIB_OUTPUT_PATH}
)
