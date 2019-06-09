#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <vector>
#include <GL\freeglut.h>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager() {};

	void load();
	GLuint getTexture(const std::string& name);
	void addTextureSource(const std::string& file);
private:
	GLuint* textures;
	std::vector<std::string> textureFiles;
	bool loadTexture(const std::string& fileName, GLuint textureID);
	std::string texturePath;
};

#endif