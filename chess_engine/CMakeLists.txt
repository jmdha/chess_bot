cmake_minimum_required(VERSION 3.0.0)
project(chess_engine VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS Classes/*.cpp Classes/*.h)

add_executable(depth1 depth1.cpp ${sources})
add_executable(depth2 depth2.cpp ${sources})
add_executable(depth3 depth3.cpp ${sources})
add_executable(depth4 depth4.cpp ${sources})
add_executable(depth5 depth5.cpp ${sources})
add_executable(depth6 depth6.cpp ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(tests/CMakeTests.txt)