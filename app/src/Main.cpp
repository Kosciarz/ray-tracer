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


    std::vector<float> vertices = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    std::vector<std::uint32_t> indices = {
        0, 1, 2,
        2, 3, 0
    };

#ifndef NDEBUG
    const auto shadersPath = fs::path(ASSETS_DIR) / "shaders";
    const auto texturesPath = fs::path(ASSETS_DIR) / "textures";
#endif

    Shader shader(shadersPath / "vs.glsl", shadersPath / "fs.glsl");

#pragma region texture

    std::uint32_t texture;
    GL_CHECK(glGenTextures(1, &texture));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    std::int32_t width, height, nrChannels;
    const auto texturePath1 = (texturesPath / "wooden_container.jpg").string();
    auto* data = stbi_load(texturePath1.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cerr << "Error: failed to load texture data" << '\n';
        return -1;
    }
    else
    {
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    }

    stbi_image_free(data);

#pragma endregion

#pragma region buffers

    VAO vao;
    vao.Bind();

    VertexBuffer buffer(vertices.data(), vertices.size() * sizeof(float));
    
    IndexBuffer indexBuffer(indices.size() * sizeof(std::uint32_t), indices.data(), GL_STATIC_DRAW);
    
    vao.AddVertexBuffer(buffer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vao.EnableVertexAttribArray(0);

    vao.AddVertexBuffer(buffer, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.EnableVertexAttribArray(1);

    vao.AddVertexBuffer(buffer, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.EnableVertexAttribArray(2);

    vao.Unbind();

#pragma endregion

    while (!window.ShouldClose())
    {
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        shader.Use();
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
        vao.Bind();
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));

        window.SwapBuffers();
        window.PollEvents();
    }
}