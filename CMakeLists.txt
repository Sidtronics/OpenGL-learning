cmake_minimum_required(VERSION 3.23.3)

project(Opengl)

add_executable(${PROJECT_NAME} OpenGL.cpp)

#GLFW config
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/GLFW)

#GLEW config
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/GLEW/build/cmake)
add_subdirectory(external/txtblocks)

#Copy resource folder to build directory
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    FILE(COPY res DESTINATION "${CMAKE_BINARY_DIR}")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC external/GLEW/include external/GLFW/include)

target_link_libraries(${PROJECT_NAME} txtblocks glew_s glfw3 -lGL)
