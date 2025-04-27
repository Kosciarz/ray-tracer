#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ray.h"

#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstdlib>

namespace fs = std::filesystem;

constexpr auto WIDTH = 1080;
constexpr auto HEIGHT = 720;

static float s_MixVisibility = 0.5f;

static void InitImGui(GLFWwindow* window);
static void ShutdownImGui();
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    auto context = GlfwContext::Create();
    if (context.IsErr())
    {
        std::cerr << "Error: " << context.Error() << '\n';
        return EXIT_FAILURE;
    }

    auto windowResult = Window::Create(WIDTH, HEIGHT, "window");
    if (windowResult.IsErr())
    {
        std::cerr << "Error: " << windowResult.Error() << '\n';
        return EXIT_FAILURE;
    }

    const auto& window = windowResult.Value();

    glfwSetKeyCallback(window->GetWindow(), KeyCallback);
    InitImGui(window->GetWindow());

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

    VAO vertexArray;
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

#pragma region texture1

    stbi_set_flip_vertically_on_load(true);

    GLuint texture1;
    GL_CHECK(glGenTextures(1, &texture1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

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

    GLuint texture2;
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

#pragma region shaders

    const auto vertexShader = shadersPath / "vs.glsl";
    const auto fragmentShader = shadersPath / "fs.glsl";

    const ShaderPaths paths{vertexShader, fragmentShader};

    const auto& shaderSource = ShaderSources::Load(paths);
    if (shaderSource.IsErr())
    {
        std::cerr << "Error: " << shaderSource.Error() << '\n';
        return EXIT_FAILURE;
    }

    const auto& shaderResult = Shader::Create(shaderSource.Value());
    if (shaderResult.IsErr())
    {
        std::cerr << "Error: " << shaderResult.Error() << '\n';
        return EXIT_FAILURE;
    }

    const auto& shader = shaderResult.Value();

    // set the texture uniforms
    shader->Use();
    shader->SetUniformInt("texture1", 0);
    shader->SetUniformInt("texture2", 1);
    shader->SetUniformFloat("visibility", s_MixVisibility);

#pragma endregion

    while (!window->ShouldClose())
    {
        ScopedTimer timer("main loop");

        window->PollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();

        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        // transform the object
        glm::mat4 transform1{1.0f};
        transform1 = glm::translate(transform1, glm::vec3{0.5, -0.5, 0.0});
        transform1 = glm::rotate(transform1, static_cast<float>(glfwGetTime()), glm::vec3{0.0, 0.0, 1.0});

        shader->Use();
        shader->SetUniformMat4("transform", glm::value_ptr(transform1));

        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
        GL_CHECK(glActiveTexture(GL_TEXTURE1));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture2));

        shader->Use();
        vertexArray.Bind();
        indexBuffer.Bind();

        // draw 1st cube
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0));

        glm::mat4 transform2{1.0f};
        transform2 = glm::translate(transform2, glm::vec3{glm::sin(glfwGetTime()), glm::cos(glfwGetTime()), 0.0});
        transform2 = glm::rotate(transform2, static_cast<float>(glfwGetTime() * -1), glm::vec3{0.0, 0.0, 1.0});
        auto scale = glm::sin(glfwGetTime());
        transform2 = glm::scale(transform2, glm::vec3{scale, scale, 0.0});

        shader->SetUniformMat4("transform", glm::value_ptr(transform2));

        // draw 2nd cube
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0));

        shader->Unuse();
        vertexArray.Unbind();
        indexBuffer.Unbind();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->SwapBuffers();
    }

    ShutdownImGui();
}

static void InitImGui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

static void ShutdownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}