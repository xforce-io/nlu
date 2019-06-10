cmake_minimum_required(VERSION 2.6.4)

project(syntax)

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

set(SYNTAX_OUTPUT_PATH syntax/)
set(SYNTAX_LIB_OUTPUT_PATH  ${SYNTAX_OUTPUT_PATH}/lib/syntax)
set(SYNTAX_INC_OUTPUT_PATH  ${SYNTAX_OUTPUT_PATH}/include/syntax)
set(SYNTAX_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -ansi -std=c++11 -DUNICODE=1 -O2")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
  ${CMAKE_SOURCE_DIR}/deps/basic/lib/basic/libbasic.a
)

add_library(syntax
  ${SEG_FILES})

target_link_libraries(syntax
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )

add_custom_command(TARGET syntax
  PRE_BUILD

  #make syntax
  COMMAND mkdir -p ${SYNTAX_LIB_OUTPUT_PATH}
  COMMAND mkdir -p ${SYNTAX_INC_OUTPUT_PATH}
  COMMAND mkdir -p ${SYNTAX_INC_OUTPUT_PATH}/public/

  COMMAND cp ${SYNTAX_SRC_DIR}/syntax.h ${SYNTAX_INC_OUTPUT_PATH}/
  COMMAND cp ${SYNTAX_SRC_DIR}/public.h ${SYNTAX_INC_OUTPUT_PATH}/
  COMMAND cp ${SYNTAX_SRC_DIR}/public/public.h ${SYNTAX_INC_OUTPUT_PATH}/public/
  COMMAND cp ${SYNTAX_SRC_DIR}/public/dep.h ${SYNTAX_INC_OUTPUT_PATH}/public/
  COMMAND git log | head -n 1 > ${SYNTAX_OUTPUT_PATH}/version
)

add_custom_command(TARGET syntax
  POST_BUILD

  #make syntax
  COMMAND cp libsyntax.a ${SYNTAX_LIB_OUTPUT_PATH}
)
