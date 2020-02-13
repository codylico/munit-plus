cmake_minimum_required(VERSION 3.0)
project(munit_plus CXX)

add_library(munit_plus STATIC munit.cpp munit.hpp)
target_compile_features(munit_plus
  PRIVATE cxx_thread_local)

option(MUNIT_TEST_EXAMPLE "Build the munit example test" OFF)

if (MUNIT_TEST_EXAMPLE)
  add_executable(munit_plus_example example.cpp)
  target_link_libraries(munit_plus_example munit_plus)
endif (MUNIT_TEST_EXAMPLE)
