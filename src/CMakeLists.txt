set(SOURCES
    "App/Application.cpp"
    "App/Window.cpp"
    "App/GlfwContext.cpp"
    "App/RayTracerLayer.cpp"

    "Utils/StbImageImpl.cpp"
    
    "Renderer/Image.cpp"
    "Renderer/Renderer.cpp"
    "Renderer/Shader.cpp"
    "Renderer/Buffer.cpp"
    "Renderer/VertexArray.cpp"

    "Core/Color.cpp"
    "Core/Ray.cpp"
)


foreach(SOURCE IN LISTS SOURCES)
    message(STATUS "Adding file ${SOURCE}")
endforeach()


add_library(RayCore STATIC ${SOURCES})
target_compile_definitions(RayCore PRIVATE 
    SHADERS_DIR="${CMAKE_SOURCE_DIR}/Shaders"
    ASSETS_DIR="${CMAKE_SOURCE_DIR}/Assets"
)
target_sources(RayCore PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(RayCore PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${STB_IMAGE_DIR}
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(RayCore PUBLIC glfw glad glm)


add_executable(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
target_link_libraries(RayTracer PRIVATE RayCore)

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(RayTracer PRIVATE /ZI)    
endif()