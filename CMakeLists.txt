cmake_minimum_required(VERSION 3.10)

option(BUILD_SAMPLES ON)

set(PROJECT_NAME polynoms)
project(${PROJECT_NAME})

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")



set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_subdirectory(UI)
include_directories(UI)

add_subdirectory(containers)
add_subdirectory(expressions)
add_subdirectory(samples)

add_subdirectory(include)

include_directories(containers)

include_directories(expressions)
include_directories(samples)

include_directories(include)


if(BUILD_TESTING)
	add_subdirectory(test)
endif()


# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")