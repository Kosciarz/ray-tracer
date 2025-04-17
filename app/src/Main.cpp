#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

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


    std::vector<float> vertexCords1 = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    std::vector<float> textureCords1 = {
        0.0f, 0.0f, 
        1.0f, 0.0f, 
        0.5f, 1.0f 
    };


#ifndef NDEBUG
    auto shaderPath = fs::path(ASSETS_DIR) / "shaders";
    auto texturePath = fs::path(ASSETS_DIR) / "textures";
#endif

    Shader shader1(shaderPath / "vs.glsl", shaderPath / "fs.glsl");

    std::uint32_t texture;
    GL_CHECK(glGenTextures(1, &texture));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
    GL_CHECK();


    VAO vao1;
    vao1.Bind();
    VertexBuffer buffer1(vertexCords1.data(), vertexCords1.size() * sizeof(float));
    vao1.AddVertexBuffer(buffer1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao1.Unbind();


    while (!window.ShouldClose())
    {
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader1.Use();
        vao1.Bind();
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, vertexCords1.size() / 3));
        vao1.Unbind();
        shader1.Unuse();

        window.SwapBuffers();
        window.PollEvents();
    }
}