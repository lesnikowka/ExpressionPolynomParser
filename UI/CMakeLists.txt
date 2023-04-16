#
# Example CMakeLists.txt file to demonstrate how to make a designable Windows Forms project with CMake.
#
# Code modifications and example by John Farrier, john.farrier@helleboreconsulting.com
#

cmake_minimum_required(VERSION 2.8.10)

# Project Name
project(ui CXX)

#include(CheckFunctionExists)
#include(CheckCXXSourceCompiles)
#include(CheckIncludeFile)

# Note: The designable form is assumed to have a .h extension as is default in Visual Studio.
# Note: The designable form is assumed to have a .resx file with the same name and path (save extension) as is default in Visual Studio

set(TARGET_H
  MainWindow.h
  TestingPolynoms.h
  )

set(TARGET_SRC
  MainWindow.cpp
  utilities.cpp
  )
set_source_files_properties(${TARGET_SRC} PROPERTIES COMPILE_FLAGS "/clr")

set(TARGET_RESX
  MainWindow.resx
  TestingPolynoms.resx
  )

set(TARGET_LIBRARIES ${SYSLIBS})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(ui ${TARGET_SRC} ${TARGET_H} ${TARGET_RESX})

target_link_libraries(ui ${TARGET_LIBRARIES})



target_include_directories(ui PUBLIC ${MP2_INCLUDE})
target_include_directories(ui PUBLIC ../include)
target_include_directories(ui PUBLIC ../containers)
target_include_directories(ui PUBLIC ../expressions)


if(NOT CMAKE_GENERATOR MATCHES "Visual Studio 1[0-6]")
  # VS 17 2022 and above require a global mark on managed assemblies.
  # CMake adds this automatically when using COMMON_LANGUAGE_RUNTIME,
  # but this test covers direct use of /clr.
  set_property(TARGET ui PROPERTY VS_GLOBAL_ManagedAssembly "true")
endif()

# Note: The property VS_GLOBAL_KEYWORD must be set.
set_property(TARGET ui PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")

# Note: The property VS_DOTNET_REFERENCES must be set.
set_property(TARGET ui PROPERTY VS_DOTNET_REFERENCES "System" "System.Data" "System.Drawing" "System.Windows.Forms" "System.Xml")

# Note: Modification of compiler flags is required for CLR compatibility now that we are using .resx files.
string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")