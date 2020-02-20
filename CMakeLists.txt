cmake_minimum_required(VERSION 3.0)
project(munit_plus CXX)

add_library(munit_plus STATIC munit.cpp munit.hpp)
target_compile_features(munit_plus
  PUBLIC cxx_rvalue_references cxx_long_long_type cxx_constexpr cxx_noexcept
  PRIVATE cxx_thread_local)

option(MUNIT_DISABLE_TIMING "disable the timing information" OFF)
option(MUNIT_TEST_EXAMPLE "Build the munit example test" OFF)

if (MUNIT_DISABLE_TIMING)
  target_compile_definitions(munit_plus
    PRIVATE "MUNIT_DISABLE_TIMING")
endif (MUNIT_DISABLE_TIMING)

if (MUNIT_TEST_EXAMPLE)
  add_executable(munit_plus_example example.cpp)
  target_link_libraries(munit_plus_example munit_plus)
  target_compile_features(munit_plus_example
    PRIVATE cxx_nullptr)
endif (MUNIT_TEST_EXAMPLE)
