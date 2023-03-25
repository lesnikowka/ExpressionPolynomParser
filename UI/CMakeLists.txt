#set(target UI)
#project(${target})
#file(GLOB hdrs "*.h*" srcs "*.cpp*")
#add_custom_target(${target} SOURCES ${hdrs} ${srcs})


set(target ui)

project(${target})

file(GLOB srcs "*.cpp*" hdrs "*.h*")

set_source_files_properties(${srcs} PROPERTIES COMPILE_FLAGS "/clr")

set(TARGET_RESX MyForm.resx)

add_executable(${target} ${srcs} ${hdrs} ${TARGET_RESX})


set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_ManagedAssembly "true")


set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES "System" "System.Data" "System.Drawing" "System.Windows.Forms" "System.Xml")

string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")



target_include_directories(${target} PUBLIC ${MP2_INCLUDE})
target_include_directories(${target} PUBLIC ../expressions)
target_include_directories(${target} PUBLIC ../containers)
target_include_directories(${target} PUBLIC ../UI)