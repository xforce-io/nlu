cmake_minimum_required(VERSION 2.6.4)

project(ner)

include_directories(
  /usr/include/
  /home/freeman/software/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  )

link_directories(
  /home/freeman/software/lib/
)

set(NER_OUTPUT_PATH ner/)
set(NER_LIB_OUTPUT_PATH  ${NER_OUTPUT_PATH}/lib/ner)
set(NER_INC_OUTPUT_PATH  ${NER_OUTPUT_PATH}/include/ner)
set(NER_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE NER_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11 -O2")

add_library(ner
  ${NER_FILES})

target_link_libraries(ner
  log4cplus
  pthread
  rt
  z
  #tcmalloc
  )

add_custom_command(TARGET ner
  PRE_BUILD

  #make ner
  COMMAND mkdir -p ${NER_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${NER_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${NER_INC_OUTPUT_PATH}/public
  COMMAND mkdir -p ${NER_INC_OUTPUT_PATH}/data

  COMMAND cp ${NER_SRC_DIR}/ner.h ${NER_INC_OUTPUT_PATH}/
  COMMAND cp ${NER_SRC_DIR}/name_entity.h ${NER_INC_OUTPUT_PATH}/
  COMMAND cp ${NER_SRC_DIR}/person_name.h ${NER_INC_OUTPUT_PATH}/
  COMMAND cp ${NER_SRC_DIR}/public.h ${NER_INC_OUTPUT_PATH}/
  COMMAND cp ${NER_SRC_DIR}/public/common.h ${NER_INC_OUTPUT_PATH}/public/
  COMMAND cp ${NER_SRC_DIR}/public/public.h ${NER_INC_OUTPUT_PATH}/public/
  COMMAND cp ${NER_SRC_DIR}/data/public.h ${NER_INC_OUTPUT_PATH}/data/
  COMMAND cp ${NER_SRC_DIR}/data/manager.h ${NER_INC_OUTPUT_PATH}/data/
  COMMAND cp ${NER_SRC_DIR}/data/surname.h ${NER_INC_OUTPUT_PATH}/data/
  COMMAND git log | head -n 1 > ${NER_OUTPUT_PATH}/version
)

add_custom_command(TARGET ner
  POST_BUILD

  #make ner
  COMMAND cp libner.a ${NER_LIB_OUTPUT_PATH}
)
