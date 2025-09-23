cmake_minimum_required(VERSION 3.31)

project(ModernLibrary)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/std:c++latest)
    add_compile_options(/std:clatest)
    add_compile_options(/experimental:module)
elseif(GCC)
    add_compile_options(-fmodules)
endif()

file(GLOB ModuleFile "ModernLibrary/Src/*.ixx")

add_executable(ModernLibrary ${ModuleFile} Execute/string_demo.cpp)

source_group("String" FILES ${ModuleFile})