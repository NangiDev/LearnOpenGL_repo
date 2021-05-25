#include <fstream>
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	// glfw: Initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For macOs
	
	// Register window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
	
	// Create shaders
	Shader shader1("shaders/vertex.vs", "shaders/fragment1.fs");
	Shader shader2("shaders/vertex.vs", "shaders/fragment2.fs");

	// Define first triangle
	float firstTraiangle[] = {
		// Positions		//Colors
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};

	// Define second triangle
	float secondTriangle[] = {
		// Positions		//Colors
		0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};

	// First triangle Array and Buffer objects
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTraiangle), firstTraiangle, GL_STATIC_DRAW);
	// Telling OpenGL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// Second triangle Array and Buffer objects
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	// Telling OpenGL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here 
	
		// Clear render buffer
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader1.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		shader2.use();
		// Pass uniform to fragment buffer 2
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) * 0.5f) + 0.5f;
		shader2.setFloat("ourColor", greenValue);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the buffers
		glfwSwapBuffers(window);

		// Check and call events
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	shader1.remove();
	shader2.remove();
	
	glfwTerminate();
	exit(EXIT_SUCCESS);
} 
