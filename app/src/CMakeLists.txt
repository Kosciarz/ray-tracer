set(SOURCES
	"Main.cpp"
    "Window.h"
    "Window.cpp"
    "Shader.h"
    "Shader.cpp"
    "VertexBuffer.h"
    "VertexBuffer.cpp"
    "VAO.h"
    "VAO.cpp"
    "IndexBuffer.h"
    "IndexBuffer.cpp"
    "Utils.h"
    "Vec3.h"
    "Vec3.cpp"
)

add_executable("RayTracer" ${SOURCES})
target_link_libraries(
    "RayTracer" PRIVATE glfw glm glad
)
target_compile_definitions("RayTracer" PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/app/assets/shaders")
target_compile_definitions("RayTracer" PRIVATE DEBUG=1)