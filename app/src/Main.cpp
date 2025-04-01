#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VAO.h"

#include <filesystem>
#include <fstream>
#include <iostream>

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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    VAO vao;
    VertexBuffer buffer(vertices, 9 * sizeof(float));
    vao.AddVertexBuffer(buffer, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    Shader shader("../../../app/shaders/vs.glsl", "../../../app/shaders/fs.glsl");

    while (!window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.SwapBuffers();
        window.PollEvents();
    }
}
