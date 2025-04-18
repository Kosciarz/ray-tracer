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
#include <cstdlib>

namespace fs = std::filesystem;

constexpr auto WIDTH = 1080;
constexpr auto HEIGHT = 720;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Window window(WIDTH, HEIGHT, "window");
    glfwSetKeyCallback(window.GetWindow(), KeyCallback);


#pragma region buffers

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

    VAO vao;
    vao.Bind();

    VertexBuffer buffer(vertices.data(), vertices.size() * sizeof(float));

    IndexBuffer indexBuffer(indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    vao.AddVertexBuffer(buffer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vao.EnableVertexAttribArray(0);

    vao.AddVertexBuffer(buffer, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.EnableVertexAttribArray(1);

    vao.AddVertexBuffer(buffer, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.EnableVertexAttribArray(2);

    vao.Unbind();

#pragma endregion

#ifndef NDEBUG
    const auto shadersPath = fs::path(ASSETS_DIR) / "shaders";
    const auto texturesPath = fs::path(ASSETS_DIR) / "textures";
#endif

    Shader shader(shadersPath / "vs.glsl", shadersPath / "fs.glsl");

    stbi_set_flip_vertically_on_load(true);

#pragma region texture1


    std::uint32_t texture1;
    GL_CHECK(glGenTextures(1, &texture1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    const std::string texturePath1 = (texturesPath / "wooden_container.jpg").string();

    std::int32_t width1, height1, nrChannels1;
    std::uint8_t* textureData1 = stbi_load(texturePath1.c_str(), &width1, &height1, &nrChannels1, 0);
    if (textureData1)
    {
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1));
        GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cerr << "Error: failed to load texture 1 data" << '\n';
    }

    stbi_image_free(textureData1);

#pragma endregion

#pragma region texture2

    std::uint32_t texture2;
    GL_CHECK(glGenTextures(1, &texture2));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture2));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    const std::string texturePath2 = (texturesPath / "awesome_face.png").string();

    std::int32_t width2, height2, nrChannels2;
    std::uint8_t* textureData2 = stbi_load(texturePath2.c_str(), &width2, &height2, &nrChannels2, 0);
    if (textureData2)
    {
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData2));
        GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cerr << "Error: failed to load texture 2 data" << '\n';
    }

    stbi_image_free(textureData2);

#pragma endregion

    // set the texture uniforms
    shader.Use();
    GL_CHECK(glUniform1i(glGetUniformLocation(shader.GetProgramID(), "texture1"), 0));
    shader.SetUniform("texture2", 1);


    while (!window.ShouldClose())
    {
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));

        GL_CHECK(glActiveTexture(GL_TEXTURE1));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture2));

        shader.Use();
        vao.Bind();
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));

        window.SwapBuffers();
        window.PollEvents();
    }
}