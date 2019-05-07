#include "Heightmap.hpp"
#include "stb_image.h"
using std::string;


Heightmap::~Heightmap()
{
}

void Heightmap::Load()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int textureWidth, textureHeight, bpp;
	//stbi_set_flip_vertically_on_load(1);

	unsigned char* imgData = stbi_load(filePath.c_str(), &textureWidth, &textureHeight, &bpp, 4);

	for (int i = 0; i < textureHeight; i++)
	{
		
	}

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		textureWidth,
		textureHeight,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);

	stbi_image_free(imgData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}