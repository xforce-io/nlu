cmake_minimum_required(VERSION 2.6.4)

project(pos_tagging)

include_directories(
  /usr/include/
  /usr/include/python3.6m/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/segmentor/include/
)

link_directories(
  /usr/lib64/
)

set(CMAKE_CXX_COMPILER g++)

set(POS_TAGGING_OUTPUT_PATH pos_tagging/)
set(POS_TAGGING_LIB_OUTPUT_PATH  ${POS_TAGGING_OUTPUT_PATH}/lib/pos_tagging)
set(POS_TAGGING_INC_OUTPUT_PATH  ${POS_TAGGING_OUTPUT_PATH}/include/pos_tagging)
set(POS_TAGGING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1 -O2")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
  ${CMAKE_SOURCE_DIR}/deps/segmentor/lib/segmentor/libsegmentor.a
)

add_library(pos_tagging
  ${SEG_FILES} src/model/details/strategy.cpp src/model/window_statistics/statistics_unit.h src/model/window_statistics/statistics_items.h src/model/window_statistics/details/statistics_items.cpp src/model/window_statistics/statistics_collection.h src/model/window_statistics/details/statistics_collection.cpp)

target_link_libraries(pos_tagging
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  python3.6m
  )

add_custom_command(TARGET pos_tagging
  PRE_BUILD

  #make pos_tagging
  COMMAND mkdir -p ${POS_TAGGING_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${POS_TAGGING_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${POS_TAGGING_INC_OUTPUT_PATH}/public/

  COMMAND cp ${POS_TAGGING_SRC_DIR}/pos_tagging.h ${POS_TAGGING_INC_OUTPUT_PATH}/
  COMMAND cp ${POS_TAGGING_SRC_DIR}/public.h ${POS_TAGGING_INC_OUTPUT_PATH}/
  COMMAND cp ${POS_TAGGING_SRC_DIR}/public/public.h ${POS_TAGGING_INC_OUTPUT_PATH}/public/
  COMMAND cp ${POS_TAGGING_SRC_DIR}/public/dep.h ${POS_TAGGING_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${POS_TAGGING_OUTPUT_PATH}/version
)

add_custom_command(TARGET pos_tagging
  POST_BUILD

  #make pos_tagging
  COMMAND cp libpos_tagging.a ${POS_TAGGING_LIB_OUTPUT_PATH}
)
