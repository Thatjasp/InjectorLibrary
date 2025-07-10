cmake_minimum_required(VERSION  3.31.5)
project(InjectorLibrary)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ELF_HEADER_FILES
./elf_headers/ElfHeaderManager.h
./elf_headers/ElfHeader.h
./elf_headers/ElfCodeCaveAlg.h
./elf_headers/ElfBinary.h

)
set(PUBLIC_HEADER_FILES 
./public_header/Injector.h
)
set(INTERFACE_FILES 
./interface/IBinaryFile.h
./interface/ICodeCaveAlg.h
)
set(${PROJECT_NAME}_SOURCE_FILES 
./source/ElfBinary.cpp
./source/ElfHeader.cpp
./source/ElfCodeCaveAlg.cpp
./source/ElfHeaderManager.cpp
./source/ElfProgramHeader.cpp
./source/ElfSectionHeader.cpp
./source/Injector.cpp
)

add_library(${PROJECT_NAME} STATIC  ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ./interface ./public_header/ ./elf_headers/)

target_link_libraries(${PROJECT_NAME})
