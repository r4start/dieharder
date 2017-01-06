cmake_minimum_required(VERSION 3.2)

project(dieharder)

set(VERSION 3.31.1)
set(BUGREPORT_URL "")
set(PACKAGE_URL "")

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Wall -Wno-unused-variable -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -Wno-unused-variable -pedantic")

find_package(GSL)
if (NOT GSL_FOUND)
  message(FATAL_ERROR "GSL not found!")
endif()

set(BIG_ENDIAN "")
include(${CMAKE_ROOT}/Modules/TestBigEndian.cmake)
test_big_endian(BIG_ENDIAN)
if (NOT BIG_ENDIAN)
  add_definitions(-DLITTLE_ENDIAN)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(RELEASED FALSE)
else()
  set(RELEASED TRUE)
endif()

configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h NEWLINE_STYLE UNIX)
configure_file(dieharder_version.h.in
               ${CMAKE_SOURCE_DIR}/dieharder_version.h
               NEWLINE_STYLE UNIX)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(libdieharder)
add_subdirectory(dieharder)
