add_executable(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
target_link_libraries(RayTracer PRIVATE RayCore)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(RayTracer PRIVATE /ZI)
endif()