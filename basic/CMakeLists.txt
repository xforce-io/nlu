cmake_minimum_required(VERSION 2.6.4)

project(basic)

include_directories(
  /usr/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  )

link_directories(
  /home/freeman/software/lib/
)

set(BASIC_OUTPUT_PATH basic/)
set(BASIC_LIB_OUTPUT_PATH  ${BASIC_OUTPUT_PATH}/lib/basic)
set(BASIC_INC_OUTPUT_PATH  ${BASIC_OUTPUT_PATH}/include/basic)
set(BASIC_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE BASIC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

message(${BASIC_FILES})

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -O2")

add_library(basic
  ${BASIC_FILES} src/model/fragment/fragment.h src/model/fragment/fragment_set.h src/model/fragment/details/fragment_set.cpp src/model/fragment/conflict_set.h src/model/fragment/details/conflict_set.cpp src/model/confidence.h src/model/details/confidence.cpp src/model/fragment/non_intersect_fragment_set.h src/model/fragment/fragment_set_multi.h src/model/fragment/fragment_set_label.h src/model/fragment/fragment_set_tree.h src/model/fragment/details/fragment_set_tree.cpp src/model/fragment/fragment_set_non_multi.h src/model/fragment/details/fragment_set_non_multi.cpp)

target_link_libraries(basic
  log4cplus
  pthread
  rt
  z
  #tcmalloc
  )

add_custom_command(TARGET basic
  PRE_BUILD

  #make basic
  COMMAND mkdir -p ${BASIC_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/public
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/data
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/pos
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/fragment

  COMMAND cp ${BASIC_SRC_DIR}/public.h ${BASIC_INC_OUTPUT_PATH}/
  COMMAND cp ${BASIC_SRC_DIR}/public/public.h ${BASIC_INC_OUTPUT_PATH}/public/
  COMMAND cp ${BASIC_SRC_DIR}/public/dep.h ${BASIC_INC_OUTPUT_PATH}/public/
  COMMAND cp ${BASIC_SRC_DIR}/data/manager.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/data/dict_item.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/data/word_dict.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/model/nlu_context.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/segment.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/confidence.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/pos/pos.h ${BASIC_INC_OUTPUT_PATH}/model/pos/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_label.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_multi.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_non_multi.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_tree.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND git log | head -n 1 > ${BASIC_OUTPUT_PATH}/version
)

add_custom_command(TARGET basic
  POST_BUILD

  #make basic
  COMMAND cp libbasic.a ${BASIC_LIB_OUTPUT_PATH}
)
