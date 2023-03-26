set(target UI)
project(${target})
file(GLOB hdrs "*.h*" srcs "*.cpp*")
add_custom_target(${target} SOURCES ${hdrs} ${srcs})
