#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Utils.h"
#include "Result.h"
#include "GlfwContext.h"
#include "Texture.h"

#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstdlib>


namespace fs = std::filesystem;

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

template <typename T>
bool CheckError(const Result<T>& result)
{
    if (result.IsErr())
    {
        std::cerr << "Error: " << result.Error() << '\n';
        return true;
    }
    return false;
}

int main()
{
    auto context = GlfwContext::Create();
    if (CheckError(context))
        return EXIT_FAILURE;

    auto windowResult = Window::Create();
    if (CheckError(windowResult))
        return EXIT_FAILURE;

    const auto& window = windowResult.Value();
    glfwSetKeyCallback(window->GetWindow(), KeyCallback);


    const std::vector<float> vertices = {
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
    };

    const std::vector<std::uint16_t> indices = {
        0, 1, 2,
        2, 3, 0
    };

#pragma region buffers

    VertexArray vertexArray;
    vertexArray.Bind();

    VertexBuffer vertexBuffer(vertices.data(), vertices.size() * sizeof(float));
    IndexBuffer indexBuffer(indices.size() * sizeof(std::uint16_t), indices.data(), GL_STATIC_DRAW);

    vertexArray.AddVertexBuffer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    vertexArray.EnableVertexAttribArray(0);

    vertexArray.AddVertexBuffer(vertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray.EnableVertexAttribArray(1);

    vertexArray.Unbind();

#pragma endregion

#ifndef NDEBUG
    const auto shadersPath = fs::path{ASSETS_DIR} / "shaders";
    const auto texturesPath = fs::path{ASSETS_DIR} / "textures";
#endif  

#pragma region shaders

    const auto& shaderSource = ShaderSources::Load({shadersPath / "vs.glsl", shadersPath / "fs.glsl"});
    if (CheckError(shaderSource))
        return EXIT_FAILURE;

    const auto& shaderResult = Shader::Create(shaderSource.Value());
    if (CheckError(shaderResult))
        return EXIT_FAILURE;

    const auto& shader = shaderResult.Value();

    Texture texture1{GL_TEXTURE_2D, GL_TEXTURE0, texturesPath / "wooden_container.jpg"};
    Texture texture2{GL_TEXTURE_2D, GL_TEXTURE1, texturesPath / "awesome_face.png"};

    shader->Use();
    shader->SetUniformInt("texture1", 0);
    shader->SetUniformInt("texture2", 1);

#pragma endregion

    while (!window->ShouldClose())
    {
        window->PollEvents();

        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        texture1.Bind();
        texture2.Bind();

        shader->Use();
        vertexArray.Bind();
        indexBuffer.Bind();

        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0));

        window->SwapBuffers();
    }
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}