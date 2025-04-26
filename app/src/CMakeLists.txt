set(SOURCES
    "Window.cpp"
    "Shader.cpp"
    "VertexBuffer.cpp"
    "VAO.cpp"
    "IndexBuffer.cpp"
    "Vec3.cpp"
    "StbImageImpl.cpp"
    "ShaderSource.cpp"
    "GlfwContext.cpp"
)

set(HEADERS
    "Ray.h"
    "Window.h"
    "Shader.h"
    "VertexBuffer.h"
    "VAO.h"
    "IndexBuffer.h"
    "Utils.h"
    "Vec3.h"
    "Timer.h"
    "Random.h"
    "ShaderSource.h"
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