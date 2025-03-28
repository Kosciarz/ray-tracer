#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

constexpr int width = 720;
constexpr int height = 480;

void FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(width, height, "window", NULL, NULL);
	if (!window)
	{
		std::cerr << "Error: failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	const int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		std::cerr << "Error: failed to initialize glad" << '\n';
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

