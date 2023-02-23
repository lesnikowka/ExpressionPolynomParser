set(target samples)

project(${target})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp*")

add_custom_target(${target} SOURCES ${hdrs} ${srcs})