add_subdirectory(RayTracer)

add_executable(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
target_link_libraries(RayTracer PRIVATE RayCore)
target_compile_definitions(RayTracer PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")