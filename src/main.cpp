#include <fstream>
#include <iostream>
#include <math.h>
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
	string fragment1 = readShader("shaders/fragment1.c");
	const char *fragmentShader1Source = fragment1.c_str();
	string fragment2 = readShader("shaders/fragment2.c");
	const char *fragmentShader2Source = fragment2.c_str();
	
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

	// Compile and pass first fragment shader
	unsigned int fragment1Shader;
	fragment1Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment1Shader, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragment1Shader);
			
	// Check compilation of first fragment shader
	glGetShaderiv(fragment1Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment1Shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	
	// Compile and pass second fragment shader
	unsigned int fragment2Shader;
	fragment2Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment2Shader, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragment2Shader);
			
	// Check compilation of sedond fragment shader
	glGetShaderiv(fragment2Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment2Shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Link to first shader program object
	unsigned int shader1Program;
	shader1Program = glCreateProgram();
	glAttachShader(shader1Program, vertexShader);
	glAttachShader(shader1Program, fragment1Shader);
	glLinkProgram(shader1Program);

	// Check linking of first shader program
	glGetProgramiv(shader1Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader1Program, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// Link to second shader program object
	unsigned int shader2Program;
	shader2Program = glCreateProgram();
	glAttachShader(shader2Program, vertexShader);
	glAttachShader(shader2Program, fragment2Shader);
	glLinkProgram(shader2Program);

	// Check linking of first shader program
	glGetProgramiv(shader2Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader2Program, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// Delete already linked shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragment1Shader);
	glDeleteShader(fragment2Shader);

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

		glUseProgram(shader1Program);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(shader2Program);
		// Pass uniform to fragment buffer 2
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) * 0.5f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shader2Program, "ourColor");
		glUniform4f(vertexColorLocation, 0.f, greenValue, 0.f, 1.f);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the buffers
		glfwSwapBuffers(window);

		// Check and call events
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shader1Program);
	glDeleteProgram(shader2Program);
	
	glfwTerminate();
	exit(EXIT_SUCCESS);
} 
