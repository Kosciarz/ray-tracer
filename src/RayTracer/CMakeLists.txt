set(SOURCES
    "Application.cpp"
    "Window.cpp"
    "StbImageImpl.cpp"
    "GlfwContext.cpp"

    "Renderer/Texture.cpp"
    "Renderer/Renderer.cpp"
    "Renderer/Shader.cpp"
    "Renderer/Buffer.cpp"
    "Renderer/VertexArray.cpp"
)

set(HEADERS
    "RayTracerGL.h"
    "Application.h"
    "Window.h"
    "Utils.h"
    "Result.h"
    "GlfwContext.h"

    "Renderer/Texture.h"
    "Renderer/Renderer.h"
    "Renderer/Shader.h"
    "Renderer/Buffer.h"
    "Renderer/VertexArray.h"
)

foreach(SOURCE IN LISTS SOURCES HEADERS)
    message(STATUS "Adding file ${SOURCE}")
endforeach()

add_library(RayCore STATIC ${SOURCES} ${HEADERS})
target_link_libraries(RayCore PUBLIC glfw glm glad)
target_include_directories(RayCore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${STB_IMAGE_DIR}
)
target_compile_definitions(RayCore PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")