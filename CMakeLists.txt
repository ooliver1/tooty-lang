cmake_minimum_required(VERSION 3.12)
project(tooty VERSION 0.0.0)
include_directories(./include)
include_directories(./src)

include(CTest)
enable_testing()

file(GLOB tooty_src CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(tooty main.cpp ${tooty_src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
