cmake_minimum_required(VERSION 3.21)
project(Project2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O0 -g -w")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(
    ${PROJECT_NAME}
    SHARED
    
    # Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fsm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/message.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fake_receiver.cpp
)

target_link_libraries(${PROJECT_NAME}
    # Other libraries, if any
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(project_2 main.cpp)
target_link_libraries(project_2 ${PROJECT_NAME})

set_target_properties(project_2 PROPERTIES INSTALL_RPATH "@loader_path/../lib")
