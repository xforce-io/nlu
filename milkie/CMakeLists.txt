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

set(CMAKE_CXX_COMPILER g++)

set(MILKIE_OUTPUT_PATH milkie/)
set(MILKIE_LIB_OUTPUT_PATH  ${MILKIE_OUTPUT_PATH}/lib/milkie)
set(MILKIE_INC_OUTPUT_PATH  ${MILKIE_OUTPUT_PATH}/include/milkie)
set(MILKIE_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE MILKIE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -Wno-sign-compare -ansi -std=c++11 -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

find_library(LUA_LIBRARY lua ./3rd/lua-5.3.5/lib NO_DEFAULT_PATH)

add_library(milkie
  ${MILKIE_FILES})

target_link_libraries(milkie
  ${LIB_DEPS}
  ${LUA_LIBRARY}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET milkie 
  PRE_BUILD

  #make milkie
  COMMAND mkdir -p ${MILKIE_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${MILKIE_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${MILKIE_INC_OUTPUT_PATH}/public
  COMMAND mkdir -p ${MILKIE_INC_OUTPUT_PATH}/core/model/feature_extractor
  COMMAND mkdir -p ${MILKIE_INC_OUTPUT_PATH}/core/model/context
  COMMAND mkdir -p ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence

  COMMAND cp ${MILKIE_SRC_DIR}/milkie.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND cp ${MILKIE_SRC_DIR}/errno.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND cp ${MILKIE_SRC_DIR}/public.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND cp ${MILKIE_SRC_DIR}/public/public.h ${MILKIE_INC_OUTPUT_PATH}/public/
  COMMAND cp ${MILKIE_SRC_DIR}/public/dep.h ${MILKIE_INC_OUTPUT_PATH}/public/
  COMMAND cp ${MILKIE_SRC_DIR}/public/aho_corasick.hpp ${MILKIE_INC_OUTPUT_PATH}/public/
  COMMAND cp ${MILKIE_SRC_DIR}/manager/manager.h ${MILKIE_INC_OUTPUT_PATH}/manager/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/feature_extractor/feature_extractor.h ${MILKIE_INC_OUTPUT_PATH}/core/model/feature_extractor/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/context/context.h ${MILKIE_INC_OUTPUT_PATH}/core/model/context/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/context/storage_key.h ${MILKIE_INC_OUTPUT_PATH}/core/model/context/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/context/storage_val.h ${MILKIE_INC_OUTPUT_PATH}/core/model/context/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/context/storage_item.h ${MILKIE_INC_OUTPUT_PATH}/core/model/context/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/sentence/sentence.h ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/sentence/sentence_feature.h ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/sentence/sentence_feature_chunk.h ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/sentence/sentence_feature_content.h ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence/
  COMMAND cp ${MILKIE_SRC_DIR}/core/model/sentence/sentence_feature_segment.h ${MILKIE_INC_OUTPUT_PATH}/core/model/sentence/

  COMMAND git log | head -n 1 > ${MILKIE_OUTPUT_PATH}/version
)

add_custom_command(TARGET milkie
  POST_BUILD

  #make milkie
  COMMAND cp libmilkie.a ${MILKIE_LIB_OUTPUT_PATH}
)
