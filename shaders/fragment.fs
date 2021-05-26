#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture, TexCoord) * vec4(vertexColor, 1.0f);
}
