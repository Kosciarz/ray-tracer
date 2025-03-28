cmake_minimum_required(VERSION 3.20)

project("RayTracer" LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG latest
	GIT_SHALLOW true
)

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

find_package(OpenGL)

FetchContent_MakeAvailable(GLFW glm glad)

add_subdirectory("app")
