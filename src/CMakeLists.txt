set(SOURCES
    "App/Application.cpp"
    "App/Window.cpp"
    "App/Layer.cpp"
    "App/LayerStack.cpp"
    "App/RayTracerLayer.cpp"
    "App/ImGuiLayer.cpp"

    "Events/ApplicationEvents.cpp"

    "Renderer/Image.cpp"
    "Renderer/Shader.cpp"
    "Renderer/Buffer.cpp"
    "Renderer/VertexArray.cpp"

    "Utils/StbImageImpl.cpp"

    "Core/Color.cpp"
    "Core/Ray.cpp"
    "Core/Hittable.cpp"
    "Core/HittableList.cpp"
    "Core/Sphere.cpp"
    "Core/Interval.cpp"
    "Core/Camera.cpp"
)

set(HEADERS
    "App/Application.hpp"
    "App/Window.hpp"
    "App/Layer.hpp"
    "App/LayerStack.hpp"
    "App/RayTracerLayer.hpp"
    "App/ImGuiLayer.hpp"

    "Events/Event.hpp"
    "Events/ApplicationEvents.hpp"

    "Renderer/OpenGLHeaders.hpp"
    "Renderer/Image.hpp"
    "Renderer/Shader.hpp"
    "Renderer/Buffer.hpp"
    "Renderer/VertexArray.hpp"

    "Utils/RayTracerUtils.hpp"
    "Utils/GLUtils.hpp"
    "Utils/Result.hpp"
    "Utils/Random.hpp"
    "Utils/Timer.hpp"

    "Core/Color.hpp"
    "Core/Ray.hpp"
    "Core/Hittable.hpp"
    "Core/HittableList.hpp"
    "Core/Sphere.hpp"
    "Core/Interval.hpp"
    "Core/Camera.hpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(RayCore STATIC ${SOURCES} ${HEADERS})
target_compile_definitions(RayCore PRIVATE
    SHADERS_DIR="${CMAKE_SOURCE_DIR}/Shaders"
    ASSETS_DIR="${CMAKE_SOURCE_DIR}/Assets"
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
target_include_directories(RayCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}

    PRIVATE
    ${STB_IMAGE_DIR}
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(RayCore PUBLIC glfw glad glm)

add_executable(RayTracer "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
target_link_libraries(RayTracer PRIVATE RayCore)
