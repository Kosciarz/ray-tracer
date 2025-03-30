#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <iostream>

static std::string LoadShaderSource(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Error: failed to open shader file: " << filePath << '\n';
        return "";
    }
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

static std::uint32_t CompileShader(const std::uint32_t shaderType, const std::filesystem::path& filePath)
{
    const auto shaderSource = LoadShaderSource(filePath);
    if (shaderSource.empty())
        return 0;

    const char* sourcePtr = shaderSource.c_str();
    std::uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &(sourcePtr), NULL);
    glCompileShader(shader);

    std::int32_t success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char message[512];
        glGetShaderInfoLog(shader, 512, NULL, message);
        std::cerr << "Error: failed to compile "
                  << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader" << '\n'
                  << message << '\n';
    }
    return shader;
}

static std::uint32_t CreateShader()
{
    std::uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, "../../../app/shaders/vs.glsl");
    std::uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "../../../app/shaders/fs.glsl");
    if (!vertexShader || !fragmentShader)
        return 0;

    std::uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    std::int32_t success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        char message[512];
        glGetProgramInfoLog(program, 512, NULL, message);
        std::cerr << "Error: failed to link program" << '\n'
                  << message << '\n';

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
}

void FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1080, 720, "window", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cerr << "Error: failed to initialize glad" << '\n';
        glfwTerminate();
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, -0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    std::uint32_t VBO;
    glGenBuffers(1, &VBO);

    std::uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::uint32_t shader = CreateShader();
    glUseProgram(shader);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
}
