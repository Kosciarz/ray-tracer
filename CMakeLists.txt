cmake_minimum_required(VERSION 3.20)

project("RayTracer" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

FetchContent_Declare(
	glfw3
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG latest
	GIT_SHALLOW true
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.1 
	GIT_SHALLOW true
)

FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad
	GIT_TAG v2.0.8
	GIT_SHALLOW true
)

find_package(OpenGL REQUIRED)

FetchContent_MakeAvailable(glfw3 glm glad)

add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6)

add_subdirectory(app)
