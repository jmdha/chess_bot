cmake_minimum_required(VERSION 3.0.0)
project(chess_engine VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS Classes/*.cpp Classes/*.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(Engines/CMakeList.txt)
include(tests/CMakeTests.txt)