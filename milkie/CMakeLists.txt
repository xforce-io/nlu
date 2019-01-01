cmake_minimum_required(VERSION 2.6.4)

project(milkie)

include_directories(
  /usr/include/
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/include/
)

link_directories(
)

FILE(GLOB_RECURSE SEG_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Wno-deprecated -Wno-invalid-offsetof -Wno-strict-aliasing -std=c++11")
set(LIB_DEPS 
  ${CMAKE_SOURCE_DIR}/deps/public-cpp/lib/public-cpp/libpublic-cpp.a
)

add_executable(milkie
  ${SEG_FILES} src/core/model/public.h src/core/public.h src/public.h src/core/model/pattern_expr/public.h src/core/model/variable/public.h src/core/model/refer/public.h)

target_link_libraries(milkie
  ${LIB_DEPS}
  log4cplus
  pthread
  rt
  z
  )
