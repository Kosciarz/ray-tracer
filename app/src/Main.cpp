#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VAO.h"
#include "VertexBuffer.h"
#include "Window.h"
#include "IndexBuffer.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Window window(1080, 720, "window");
    glfwSetKeyCallback(window.GetWindow(), KeyCallback);

    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cerr << "Error: failed to initialize glad" << '\n';
        glfwTerminate();
        return -1;
    }

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    std::vector<std::uint32_t> indices = {
        0, 1, 2,
        2, 3, 0};

    Shader shader("../../../app/shaders/vs.glsl", "../../../app/shaders/fs.glsl");

    VAO vao;
    vao.Bind();
    VertexBuffer buffer(vertices.data(), vertices.size() * sizeof(float));
    IndexBuffer elementBuffer(indices.data(), indices.size() * sizeof(std::uint32_t));

    vao.AddVertexBuffer(buffer, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.Unbind();

    while (!window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        window.SwapBuffers();
        window.PollEvents();
    }
}
