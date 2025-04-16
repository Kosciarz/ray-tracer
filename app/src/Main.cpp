#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VAO.h"
#include "VertexBuffer.h"
#include "Window.h"
#include "IndexBuffer.h"
#include "Utils.h"

#include <filesystem>
#include <vector>
#include <cstdint>

namespace fs = std::filesystem;

constexpr std::uint16_t WIDTH = 1080;
constexpr std::uint16_t HEIGHT = 720;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Window window(WIDTH, HEIGHT, "window");
    glfwSetKeyCallback(window.GetWindow(), KeyCallback);


    std::vector<float> vertices1 = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    std::vector<float> vertices2 = {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.0f
    };

#ifdef DEBUG
    fs::path shaderPath{SHADER_DIR};
#endif

    Shader shader1(shaderPath / "vs.glsl", shaderPath / "fs.glsl");
    Shader shader2(shaderPath / "vs.glsl", shaderPath / "yellowfs.glsl");

    VAO vao1;
    vao1.Bind();
    VertexBuffer buffer1(vertices1.data(), vertices1.size() * sizeof(float));
    vao1.AddVertexBuffer(buffer1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao1.Unbind();

    VAO vao2;
    vao2.Bind();
    VertexBuffer buffer2(vertices2.data(), vertices2.size() * sizeof(float));
    vao2.AddVertexBuffer(buffer2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao2.Unbind();

    while (!window.ShouldClose())
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader1.Use();
        vao1.Bind();
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, vertices2.size() / 3));
        vao1.Unbind();
        shader1.Unuse();

        shader2.Use();
        vao2.Bind();
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, vertices2.size() / 3));
        vao2.Unbind();
        shader2.Unuse();

        window.SwapBuffers();
        window.PollEvents();
    }

}
