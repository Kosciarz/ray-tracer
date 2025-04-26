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

namespace fs = std::filesystem;

constexpr auto WIDTH = 1080;
constexpr auto HEIGHT = 720;

static float s_MixVisibility = 0.5f;

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

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Window window{WIDTH, HEIGHT, "window"};
    glfwSetKeyCallback(window.GetWindow(), KeyCallback);
    InitImGui(window.GetWindow());

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

#pragma region buffers classes
    //
    //    VAO vao;
    //    vao.Bind();
    //
    //    VertexBuffer buffer(vertices.data(), vertices.size() * sizeof(float));
    //
    //    IndexBuffer indexBuffer(indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
    //
    //    vao.AddVertexBuffer(buffer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //    vao.EnableVertexAttribArray(0);
    //
    //    vao.AddVertexBuffer(buffer, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //    vao.EnableVertexAttribArray(1);
    //
    //    vao.AddVertexBuffer(buffer, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //    vao.EnableVertexAttribArray(2);
    //
    //    vao.Unbind();
    //
#pragma endregion

#pragma region buffers raw

    GLuint vbo, vao, ebo;

    // vertex array object (VAO) - holds information about multiple VBOs and can switch between them
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));

    // vertex buffer object (VBO) - holds vertices
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));

    // element buffer object (EBO) - holds indices of selected vertices
    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint16_t), indices.data(), GL_STATIC_DRAW));

    // bind data into VAO
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glBindVertexArray(0));

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

    const auto vertexShader = shadersPath / "vs.glsl";
    const auto fragmentShader = shadersPath / "fs.glsl";

    const auto shaderSource = ShaderSource::Load(vertexShader, fragmentShader);
    if (!shaderSource.IsValid())
    {
        std::cerr << "Error: Failed to load shader sources" << '\n'
            << "Vertex Shader: " << vertexShader << '\n'
            << "Fragment Shader: " << fragmentShader << '\n';
        return -1;
    }

    Shader shader{shaderSource};

    // set the texture uniforms
    shader.Use();
    shader.SetUniformInt("texture1", 0);
    shader.SetUniformInt("texture2", 1);
    shader.SetUniformFloat("visibility", s_MixVisibility);
    shader.Unuse();


    while (!window.ShouldClose())
    {
        ScopedTimer timer("main loop");

        window.PollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        // transform the object
        glm::mat4 transform1{1.0f};
        transform1 = glm::translate(transform1, glm::vec3{0.5, -0.5, 0.0});
        transform1 = glm::rotate(transform1, static_cast<float>(glfwGetTime()), glm::vec3{0.0, 0.0, 1.0});

        shader.Use();
        shader.SetUniformMat4("transform", glm::value_ptr(transform1));
        shader.Unuse();

        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
        GL_CHECK(glActiveTexture(GL_TEXTURE1));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture2));

        shader.Use();
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
        
        // draw 1st cube
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0));
        
        shader.Unuse();
        GL_CHECK(glBindVertexArray(0));
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        auto transform2 = glm::translate(glm::mat4{1.0f}, glm::vec3{glm::sin(glfwGetTime()), glm::cos(glfwGetTime()), 0.0});
        transform2 = glm::rotate(transform2, static_cast<float>(glfwGetTime() * -1), glm::vec3{0.0, 0.0, 1.0});
        auto scale = glm::sin(glfwGetTime());
        transform2 = glm::scale(transform2, glm::vec3{scale, scale, 0.0});

        shader.Use();
        shader.SetUniformMat4("transform", glm::value_ptr(transform2));
        shader.Unuse();

        shader.Use();
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

        // draw 2nd cube
        GL_CHECK(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0));

        shader.Unuse();
        GL_CHECK(glBindVertexArray(0));
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}