#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float xOffset;
out vec3 vertexColor;
void main()
{
	gl_Position = vec4(aPos * vec3(1.0f, -1.0f, 1.0f) + vec3(xOffset, 0.0f, 0.0f), 1.0);
	vertexColor = aColor;
}
