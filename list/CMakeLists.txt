set(target list)

project(${target})

file(GLOB hdrs "*.h*")

add_custom_target(${target} SOURCES ${hdrs})