cmake_minimum_required(VERSION 3.20)

project("RayTracer" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

FetchContent_Declare(
	glfw3
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG latest
	GIT_SHALLOW TRUE
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.1 
	GIT_SHALLOW TRUE
)

FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad
	GIT_TAG v2.0.8
	GIT_SHALLOW TRUE
)

find_package(OpenGL REQUIRED)

set(STB_IMAGE_DIR ${CMAKE_BINARY_DIR}/external/stb)
if(NOT EXISTS ${STB_IMAGE_DIR}/stb_image.h)
	file(
		DOWNLOAD
		https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
		${STB_IMAGE_DIR}/stb_image.h
		TLS_VERIFY ON
	)
endif()

FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG docking
	GIT_SHALLOW TRUE
)

FetchContent_Declare(
	gtest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG v1.16.0
	GIT_SHALLOW TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw3 glm glad imgui gtest)

add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6)

add_subdirectory("app")