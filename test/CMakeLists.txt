set(target ${MP2_TESTS})
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")


enable_testing()
add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} GTest::gtest_main)
target_include_directories(${target} PUBLIC ../expressions)
include(GoogleTest)
gtest_discover_tests(${target})