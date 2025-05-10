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
    "Core/Sphere.cpp"
)

set(HEADERS
    "App/Application.hpp"
    "App/Window.hpp"
    "App/GlfwContext.hpp"
    "App/Layer.hpp"
    "App/RayTracerLayer.hpp"

    "Utils/Result.hpp"
    "Utils/Utils.hpp"
    "Utils/Random.hpp"
    "Utils/Timer.hpp"

    "Renderer/OpenGLHeaders.hpp"
    "Renderer/Image.hpp"
    "Renderer/Renderer.hpp"
    "Renderer/Shader.hpp"
    "Renderer/Buffer.hpp"
    "Renderer/VertexArray.hpp"

    "Core/Color.hpp"
    "Core/Ray.hpp"
    "Core/Hittable.hpp"
    "Core/Sphere.hpp"
)

foreach(SOURCE IN LISTS SOURCES HEADERS)
    message(STATUS "Adding file ${SOURCE}")
endforeach()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})


add_library(RayCore STATIC ${SOURCES} ${HEADERS})
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