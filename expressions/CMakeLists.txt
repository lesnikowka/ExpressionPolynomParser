set(target expressions)

project(${target})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})


target_include_directories(${target} PUBLIC ${MP2_INCLUDE})
target_include_directories(${target} PUBLIC ../include)
target_include_directories(${target} PUBLIC ../containers)
target_include_directories(${target} PUBLIC ../UI)
