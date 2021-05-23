#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

const string readShader(const string path)
{
	string content;
	ifstream fileStream(path, ios::in);

	if(!fileStream.is_open())
	{
		cout << "Could not read file " << path << ". File does not exist!" << endl;
		return "";
	}

	string line = "";
	while(true)
	{
		getline(fileStream, line);
		if (fileStream.eof()) break;
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
};

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
	
	// Read shaders
	string vertex = readShader("shaders/vertex.c");
	const char *vertexShaderSource = vertex.c_str();
	string fragment = readShader("shaders/fragment.c");
	const char *fragmentShaderSource = fragment.c_str();
	
	// Compile and pass vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
			
	// Check compilation of vertex shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Compile and pass fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
			
	// Check compilation of fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Link to shader program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check linking of shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// Delete already linked shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Define triangle vertices
	float vertices[] = {
		// First triangle
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		// Second triangle
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Telling OpenGL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here 
		
		// Clear render buffer
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Draw arrays as triangles
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 3);

		// Swap the buffers
		glfwSwapBuffers(window);

		// Check and call events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	
	glfwTerminate();
	exit(EXIT_SUCCESS);
} 
