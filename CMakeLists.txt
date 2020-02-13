cmake_minimum_required(VERSION 3.0)
project(munit_plus C)

add_library(munit STATIC munit.c munit.h)

option(MUNIT_TEST_EXAMPLE "Build the munit example test" OFF)

if (MUNIT_TEST_EXAMPLE)
  add_executable(munit_example example.c)
  target_link_libraries(munit_example munit)
endif (MUNIT_TEST_EXAMPLE)
