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
    "StbImageImpl.cpp"
    "Timer.h"
)

add_executable("RayTracer" ${SOURCES})
target_link_libraries(
    "RayTracer" PRIVATE glfw glm glad
)
target_include_directories("RayTracer" PRIVATE ${STB_IMAGE_DIR})
target_compile_definitions("RayTracer" PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/app/assets")