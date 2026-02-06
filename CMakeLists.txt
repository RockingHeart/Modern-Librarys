cmake_minimum_required(VERSION 3.31)

project(ModernLibrary)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/std:c++latest)
    add_compile_options(/std:clatest)
    add_compile_options(/experimental:module)
    add_compile_options(/permissive-)
else()
    add_compile_options(-fmodules)
endif()

file(GLOB StringPath "ModernLibrary/Src/String/*.ixx")
file(GLOB FixedVectorPath "ModernLibrary/Src/FixedVector/*.ixx")
file(GLOB VectorPath "ModernLibrary/Src/Vector/*.ixx")
file(GLOB WrapPath "ModernLibrary/Src/Wrap/*.ixx")
file(GLOB UtilityPath "ModernLibrary/Src/Utility/*.ixx")

add_executable(ModernLibrary
    ModernLibrary/Execute/main.cpp
)

target_sources(ModernLibrary
    PRIVATE
    FILE_SET mods TYPE CXX_MODULES
    FILES ${UtilityPath}
    FILES ${WrapPath}
    FILES ${StringPath}
    FILES ${VectorPath}
    FILES ${FixedVectorPath}
)

source_group("String" FILES ${StringPath})
source_group("Vector" FILES ${VectorPath})
source_group("FixedVector" FILES ${FixedVectorPath})
source_group("Wrap" FILES ${WrapPath})
source_group("Utility" FILES ${UtilityPath})

source_group("Execute" ModernLibrary/Execute/main.cpp)