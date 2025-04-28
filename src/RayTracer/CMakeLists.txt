set(SOURCES
    "Application.cpp"
    "Window.cpp"
    "Renderer.cpp"
    "Shader.cpp"
    "Texture.cpp"
    "VertexBuffer.cpp"
    "VertexArray.cpp"
    "IndexBuffer.cpp"
    "StbImageImpl.cpp"
    "GlfwContext.cpp"
)

set(HEADERS
    "Application.h"
    "Window.h"
    "Renderer.h"
    "Shader.h"
    "Texture.h"
    "VertexBuffer.h"
    "VertexArray.h"
    "IndexBuffer.h"
    "Utils.h"
    "Result.h"
    "GlfwContext.h"
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