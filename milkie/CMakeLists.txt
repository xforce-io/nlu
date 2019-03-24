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
  ${MILKIE_FILES} src/core/model/context/storage_key.h src/core/model/pattern_item/details/pattern_item_reg.cpp src/core/model/pattern_item/pattern_item_reg.h src/core/model/function/feature_extractor/parser/struct_feature_extractor.h src/core/model/function/feature_extractor/instruction_feature_extractor.h src/core/model/function/feature_extractor/details/instruction_feature_extractor.cpp src/core/model/function/feature_extractor/parser/details/struct_feature_extractor.cpp src/core/model/pattern/parser/details/struct_pattern.cpp src/core/model/function/feature_extractor/feature_extractor.h src/core/model/function/feature_extractor/details/feature_extractor.cpp src/errno.h src/core/model/function/manager.h src/core/model/function/details/manager.cpp src/core/model/context/storage_item.h src/core/model/pattern_item/pattern_item_syntax.h src/core/model/pattern_item/details/pattern_item_syntax.cpp src/core/model/sentence/sentence_feature_chunk.h)

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

  COMMAND cp ${MILKIE_SRC_DIR}/milkie.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND cp ${MILKIE_SRC_DIR}/public.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND cp ${MILKIE_SRC_DIR}/public/public.h ${MILKIE_INC_OUTPUT_PATH}/public/
  COMMAND cp ${MILKIE_SRC_DIR}/errno.h ${MILKIE_INC_OUTPUT_PATH}/
  COMMAND git log | head -n 1 > ${MILKIE_OUTPUT_PATH}/version
)

add_custom_command(TARGET milkie
  POST_BUILD

  #make milkie
  COMMAND cp libmilkie.a ${MILKIE_LIB_OUTPUT_PATH}
)
