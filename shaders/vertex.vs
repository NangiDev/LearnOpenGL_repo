#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float xOffset;

out vec3 vertexColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
	gl_Position = vec4(aPos + vec3(xOffset, 0.f, 0.f), 1.0f);
	gl_Position = transform * vec4(aPos, 1.0f);
	vertexColor = aColor;
	TexCoord = aTexCoord;
}
