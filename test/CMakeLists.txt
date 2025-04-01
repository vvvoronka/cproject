cmake_minimum_required(VERSION 3.21.0)

project(OptimizationsVerilogLibTests
    LANGUAGES CXX
)

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++17 -fPIC")
SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)
include(FetchContent)
include(CTest)

FetchContent_Declare(
  gtest

  # Url for googletest download.
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

set(SOURCES_TEST_ABC
  src/optimization_utils/AbcUtilsTests.cpp
)
set(SOURCES_TEST_YOSYS
  src/optimization_utils/YosysUtilsTests.cpp
)

set(AbcTest AbcUtilsTest)
set(YosysTest YosysUtilsTest)

enable_testing()

add_executable(${AbcTest} ${SOURCES_TEST_ABC})

target_link_libraries(${AbcTest} PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(${AbcTest} PRIVATE OptimizationsVerilogLib::OptimizationsVerilogLib)

target_include_directories(
    ${AbcTest} ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)


add_executable(${YosysTest} ${SOURCES_TEST_YOSYS})

target_link_libraries(${YosysTest} PRIVATE GTest::gtest_main ${EXTERNAL_LIBS})
target_link_libraries(${YosysTest} PRIVATE OptimizationsVerilogLib::OptimizationsVerilogLib)

target_include_directories(
    ${YosysTest} ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src>"
)


add_test(NAME AbcUtilsTest COMMAND ${AbcTest})
# add_test(NAME YosysUtilsTest COMMAND ${YosysTest})
