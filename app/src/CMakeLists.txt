set(SOURCES
	"Main.cpp"
    "Window.h"
    "Window.cpp"
    "Shader.h"
    "Shader.cpp"
)

add_executable("RayTracer" ${SOURCES})
target_link_libraries(
	"RayTracer" 
	PRIVATE
	glfw glm glad
)
