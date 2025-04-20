set(SOURCES
	"Main.cpp"
    "Window.cpp"
    "Shader.cpp"
    "VertexBuffer.cpp"
    "VAO.cpp"
    "IndexBuffer.cpp"
    "Vec3.cpp"
    "StbImageImpl.cpp"
)

set(HEADERS
    "Window.h"
    "Shader.h"
    "VertexBuffer.h"
    "VAO.h"
    "IndexBuffer.h"
    "Utils.h"
    "Vec3.h"
    "Timer.h"
    "Random.h"
)

add_executable("RayTracer" ${SOURCES} ${HEADERS})
target_link_libraries("RayTracer" PRIVATE glfw glm glad)
target_include_directories("RayTracer" PRIVATE ${STB_IMAGE_DIR})
target_compile_definitions("RayTracer" PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/app/assets")