#ifndef window_h
#define window_h

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

class Window
{
private:
	unsigned int SCR_WIDTH, SCR_HEIGHT;

	GLFWwindow* window = NULL;

	void static framebuffer_size_callback( GLFWwindow* window, int width, int height )
	{ 
		glViewport(0, 0, width, height); 
	}

public:
	Window(const unsigned int width, const unsigned int height)
	{
		SCR_WIDTH = width;
		SCR_HEIGHT = height;

		// glfw: Initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For macOs
		
		// Register window
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}	
		glfwMakeContextCurrent(window);

		// Register callbacks	
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			cout << "Failed to initialize GLAD" << endl;
			exit(EXIT_FAILURE);
		}
	};

	GLFWwindow* getWindow()
	{
		return window;
	}
};
#endif
