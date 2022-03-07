cmake_minimum_required(VERSION 3.22.1)
project(ECS VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE")

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Internal libraries
message("Building [${PROJECT_NAME}]...")
message(STATUS "${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${SOURCES})


# Default libraries
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
