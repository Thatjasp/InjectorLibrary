cmake_minimum_required(VERSION  3.31.5)
project(Injector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXECUTABLE_SUFFIX ".bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(InjectorLibrary)

set(${PROJECT_NAME}_SOURCE_FILES ./source/main.cpp)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})


target_link_libraries(${PROJECT_NAME} InjectorLibrary)

file(COPY "res/hello" DESTINATION "./")
#file(COPY "res/inject" DESTINATION "./")
file(COPY "res/infect" DESTINATION "./")
