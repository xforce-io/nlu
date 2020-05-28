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

set(CMAKE_CXX_COMPILER g++)

set(BASIC_OUTPUT_PATH basic/)
set(BASIC_LIB_OUTPUT_PATH  ${BASIC_OUTPUT_PATH}/lib/basic)
set(BASIC_INC_OUTPUT_PATH  ${BASIC_OUTPUT_PATH}/include/basic)
set(BASIC_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE BASIC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1")

add_library(basic
  ${BASIC_FILES} src/data/gkb/table/details/gkb_global.cpp src/model/semantic_unit/semantic_unit.h src/model/semantic_unit/semantic_unit_entity.h src/model/semantic_unit/semantic_unit_entity_set.h src/model/kg/entity.h src/model/kg/property.h src/model/semantic_unit/details/semantic_unit.cpp)

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
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/data/gkb/table
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/pos
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/pos_ctb
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/syntax
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/semantic_unit
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/fragment
  COMMAND mkdir -p ${BASIC_INC_OUTPUT_PATH}/model/analysis_tracer

  COMMAND cp ${BASIC_SRC_DIR}/basic.h ${BASIC_INC_OUTPUT_PATH}/
  COMMAND cp ${BASIC_SRC_DIR}/public.h ${BASIC_INC_OUTPUT_PATH}/
  COMMAND cp ${BASIC_SRC_DIR}/public/public.h ${BASIC_INC_OUTPUT_PATH}/public/
  COMMAND cp ${BASIC_SRC_DIR}/public/dep.h ${BASIC_INC_OUTPUT_PATH}/public/
  COMMAND cp ${BASIC_SRC_DIR}/data/manager.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/gkb.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/table.hpp ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_global.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_adj.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_adv.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_verb.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_verb_dongjie.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_verb_dongqu.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/table/gkb_prep.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/table/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_global.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_adj.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_adv.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_verb.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_verb_dongjie.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_verb_dongqu.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/gkb/entry/entry_prep.h ${BASIC_INC_OUTPUT_PATH}/data/gkb/entry/
  COMMAND cp ${BASIC_SRC_DIR}/data/word_dict.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/data/dict_item.h ${BASIC_INC_OUTPUT_PATH}/data/
  COMMAND cp ${BASIC_SRC_DIR}/model/nlu_context.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/phrase.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/segment.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/name_entity.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/confidence.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/context.h ${BASIC_INC_OUTPUT_PATH}/model/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/chunk_sep.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/chunk.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/pos/pos_tag.h ${BASIC_INC_OUTPUT_PATH}/model/pos/
  COMMAND cp ${BASIC_SRC_DIR}/model/pos_ctb/pos_ctb_tag.h ${BASIC_INC_OUTPUT_PATH}/model/pos_ctb/
  COMMAND cp ${BASIC_SRC_DIR}/model/syntax/syntax_tag.h ${BASIC_INC_OUTPUT_PATH}/model/syntax/
  COMMAND cp ${BASIC_SRC_DIR}/model/syntax/collection_syntax_tag.h ${BASIC_INC_OUTPUT_PATH}/model/syntax/
  COMMAND cp ${BASIC_SRC_DIR}/model/semantic_unit/semantic_unit.h ${BASIC_INC_OUTPUT_PATH}/model/semantic_unit/
  COMMAND cp ${BASIC_SRC_DIR}/model/semantic_unit/semantic_unit_entity.h ${BASIC_INC_OUTPUT_PATH}/model/semantic_unit/
  COMMAND cp ${BASIC_SRC_DIR}/model/semantic_unit/semantic_unit_entity_set.h ${BASIC_INC_OUTPUT_PATH}/model/semantic_unit/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_multitag.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_label.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_multi.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_non_multi.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/fragment_set_tree.hpp ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/fragment/manager_fragment_set.h ${BASIC_INC_OUTPUT_PATH}/model/fragment/
  COMMAND cp ${BASIC_SRC_DIR}/model/analysis_tracer/analysis_tracer.h ${BASIC_INC_OUTPUT_PATH}/model/analysis_tracer/
  COMMAND git log | head -n 1 > ${BASIC_OUTPUT_PATH}/version
)

add_custom_command(TARGET basic
  POST_BUILD

  #make basic
  COMMAND cp libbasic.a ${BASIC_LIB_OUTPUT_PATH}
)
