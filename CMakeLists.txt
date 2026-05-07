cmake_minimum_required(VERSION 3.31)

project(ConWeaveLib)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/std:c++latest)
    add_compile_options(/std:clatest)
    add_compile_options(/experimental:module)
    add_compile_options(/permissive-)
else()
    add_compile_options(-fmodules)
endif()

file(GLOB StringPath "ConWeave-Library/Src/String/*.ixx")
file(GLOB FixedVectorPath "ConWeave-Library/Src/FixedVector/*.ixx")
file(GLOB VectorPath "ConWeave-Library/Src/Vector/*.ixx")
file(GLOB WrapPath "ConWeave-Library/Src/Wrap/*.ixx")
file(GLOB UtilityPath "ConWeave-Library/Src/Utility/*.ixx")

add_executable(ConWeaveLib
    ConWeave-Library/Execute/main.cpp
)

target_sources(ConWeaveLib
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

source_group("Execute" ConWeave-Library/Execute/main.cpp)