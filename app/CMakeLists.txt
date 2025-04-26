add_subdirectory("src")
add_subdirectory("test")

add_executable(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")

target_sources(RayTracer PRIVATE
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(RayTracer PRIVATE RayCore)
target_include_directories(RayTracer PRIVATE 
	${imgui_SOURCE_DIR} 
	${imgui_SOURCE_DIR}/backends
)
target_compile_definitions(RayTracer PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/app/assets")