#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Util.hpp"
using std::string;

TextureManager::TextureManager()
{
	this->texturePath = Util::getExePath() + "\\textures\\";
}

void TextureManager::load()
{
	const int textureCount = textureFiles.size();
	this->textures = new GLuint[textureCount];

	glGenTextures(textureFiles.size(), textures);

	for (int i = 0; i < textureFiles.size(); i++)
	{
		loadTexture(texturePath + textureFiles[i], textures[i]);
	}
}

void TextureManager::addTextureSource(const std::string& file)
{
	textureFiles.push_back(file);
}
bool TextureManager::loadTexture(const std::string& fileName, int textureID)
{
	int w, h, bpp;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* imgData = stbi_load(fileName.c_str(), &w, &h, &bpp, 4);
	

	if (!imgData)
		return false;


	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		w,
		h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(imgData);

	return true;
}
bool TextureManager::getTexture(const std::string& name, GLuint* texture)
{
	for (int i = 0; i < textureFiles.size(); i++)
	{
		if (textureFiles[i] == name)
		{
			*texture = textures[i];
			return true;
		}
	}
	return false;
}
