cmake_minimum_required(VERSION 3.31)

if (NOT MSVC)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_SCAN ON)
endif()

project(ConWeaveLib)

set(CMAKE_CXX_STANDARD 23)
set(ConWeaveLib_Path ${CMAKE_CURRENT_SOURCE_DIR}/ConWeave-Library)

if (MSVC)
    add_compile_options(/std:c++latest)
    add_compile_options(/std:clatest)
    add_compile_options(/experimental:module)
    add_compile_options(/permissive-)
else()
    add_compile_options(-std=c++23 -stdlib=libc++)
endif()

file(GLOB ExportPath "ConWeave-Library/Export/*.ixx")

file(GLOB StringPath "ConWeave-Library/Src/String/*.ixx")
file(GLOB FixedVectorPath "ConWeave-Library/Src/FixedVector/*.ixx")
file(GLOB VectorPath "ConWeave-Library/Src/Vector/*.ixx")
file(GLOB FilerPath "ConWeave-Library/Src/Filer/*.ixx")
file(GLOB WrapPath "ConWeave-Library/Src/Wrap/*.ixx")
file(GLOB UtilityPath "ConWeave-Library/Src/Utility/*.ixx")

add_executable(ConWeaveLib
    ${ConWeaveLib_Path}/Execute/main.cpp
)

target_sources(ConWeaveLib
    PRIVATE
    FILE_SET mods TYPE CXX_MODULES
    BASE_DIRS ${ConWeaveLib_Path}/Export
    FILES
        ${ExportPath}
    BASE_DIRS ${ConWeaveLib_Path}/Src
    FILES
        ${UtilityPath}
        ${WrapPath}
        ${StringPath}
        ${FixedVectorPath}
        ${VectorPath}
        ${FilerPath}
)

source_group("Export" FILES ${ExportPath})

source_group("String" FILES ${StringPath})
source_group("FixedVector" FILES ${FixedVectorPath})
source_group("Vector" FILES ${VectorPath})
source_group("Filer" FILES ${FilerPath})
source_group("Wrap" FILES ${WrapPath})
source_group("Utility" FILES ${UtilityPath})

source_group("Execute" ${ConWeaveLib_Path}/Execute/main.cpp)