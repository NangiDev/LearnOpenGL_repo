#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include "stb_image.cpp"

using namespace std;

class Texture
{
private:

public:
	unsigned int texture;
	void flipVertcal(bool shouldFlip)
	 {
		stbi_set_flip_vertically_on_load(shouldFlip);
	 }
	Texture(const char* texturePath, unsigned int colorType = GL_RGB)
	{
		// Specify Texture repeat method for axle S (x) and T (y)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Specifiy Texture fitering and mipmap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification does not take mipmap option

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		int texWidth, texHeight, nrChannels;
		unsigned char *data = stbi_load(texturePath, &texWidth, &texHeight, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, colorType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Failed to load texture" << endl;
		}
		stbi_image_free(data);
	}
};

#endif
