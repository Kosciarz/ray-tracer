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
)

set(HEADERS

    "App/Application.h"
    "App/Window.h"
    "App/GlfwContext.h"
    "App/Layer.h"
    "App/RayTracerLayer.h"

    "Utils/Result.h"
    "Utils/Utils.h"
    "Utils/Timer.h"
    "Utils/Random.h"

    "Renderer/OpenGLHeaders.h"
    "Renderer/Image.h"
    "Renderer/Renderer.h"
    "Renderer/Shader.h"
    "Renderer/Buffer.h"
    "Renderer/VertexArray.h"
)

foreach(SOURCE IN LISTS SOURCES HEADERS)
    message(STATUS "Adding file ${SOURCE}")
endforeach()

add_library(RayCore STATIC ${SOURCES} ${HEADERS})

target_compile_definitions(RayCore PRIVATE 
    SHADERS_DIR=\"${CMAKE_SOURCE_DIR}/Shaders\"
    ASSETS_DIR=\"${CMAKE_SOURCE_DIR}/Assets\"
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
target_include_directories(RayCore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)
target_include_directories(RayCore PRIVATE 
    ${STB_IMAGE_DIR}
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(RayCore PUBLIC glfw glm glad)