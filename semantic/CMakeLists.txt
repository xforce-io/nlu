cmake_minimum_required(VERSION 2.6.4)

project(semantic)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
  ${CMAKE_SOURCE_DIR}/deps/basic/include/
  ${CMAKE_SOURCE_DIR}/deps/milkie/include/
)

link_directories(
  /usr/lib64/
)

set(CMAKE_CXX_COMPILER g++)

set(SYNTAX_OUTPUT_PATH semantic/)
set(SYNTAX_LIB_OUTPUT_PATH  ${SYNTAX_OUTPUT_PATH}/lib/semantic)
set(SYNTAX_INC_OUTPUT_PATH  ${SYNTAX_OUTPUT_PATH}/include/semantic)
set(SYNTAX_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

add_library(semantic
  ${SEG_FILES})

target_link_libraries(semantic
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET semantic
  PRE_BUILD

  #make semantic
  COMMAND mkdir -p ${SYNTAX_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${SYNTAX_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${SYNTAX_INC_OUTPUT_PATH}/public/

  COMMAND cp ${SYNTAX_SRC_DIR}/semantic.h ${SYNTAX_INC_OUTPUT_PATH}/
  COMMAND cp ${SYNTAX_SRC_DIR}/public.h ${SYNTAX_INC_OUTPUT_PATH}/
  COMMAND cp ${SYNTAX_SRC_DIR}/public/public.h ${SYNTAX_INC_OUTPUT_PATH}/public/
  COMMAND cp ${SYNTAX_SRC_DIR}/public/dep.h ${SYNTAX_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${SYNTAX_OUTPUT_PATH}/version
)

add_custom_command(TARGET semantic
  POST_BUILD

  #make semantic
  COMMAND cp libsemantic.a ${SYNTAX_LIB_OUTPUT_PATH}
)
