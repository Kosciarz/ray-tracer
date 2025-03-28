set(SOURCES
	"Main.cpp"
)

add_executable("RayTracer" ${SOURCES})
target_link_libraries(
	"RayTracer" 
	PRIVATE
	glfw glm glad
)
