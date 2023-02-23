cmake_minimum_required(VERSION 3.10)

option(BUILD_SAMPLES ON)

set(PROJECT_NAME polynoms)
project(${PROJECT_NAME})

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")


add_subdirectory(UI)
add_subdirectory(containers)
add_subdirectory(expressions)
add_subdirectory(list)
add_subdirectory(samples)

add_subdirectory(include)


include_directories(containers)
include_directories(UI)
include_directories(expressions)
include_directories(list)
include_directories(samples)

include_directories(include)



if(BUILD_TESTING)
    add_subdirectory(gtest)
	add_subdirectory(test)
endif()


# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")