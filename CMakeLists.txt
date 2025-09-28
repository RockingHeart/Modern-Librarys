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

file(GLOB StringPath "ModernLibrary/Src/String/*.ixx")
file(GLOB UtilityPath "ModernLibrary/Src/Utility/*.ixx")

add_executable(ModernLibrary
    ${StringPath}
    ${UtilityPath}
    ModernLibrary/Execute/main.cpp
)

source_group("String" FILES ${StringPath})
source_group("Utility" FILES ${UtilityPath})

source_group("Execute" ModernLibrary/Execute/main.cpp)