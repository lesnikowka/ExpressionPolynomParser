

set(target samples)

project(${target})

file(GLOB srcs "*.cpp*")

add_executable(${target} ${srcs})

target_include_directories(${target} PUBLIC ${MP2_INCLUDE})
target_include_directories(${target} PUBLIC ../expressions)
target_include_directories(${target} PUBLIC ../containers)
target_include_directories(${target} PUBLIC ../UI)
