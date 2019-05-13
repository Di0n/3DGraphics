#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <string>
#include <Windows.h>
#include <gl\GL.h>

class Heightmap
{
public:
	Heightmap(const std::string& filePath)
		: filePath(filePath) {}
	~Heightmap();

	void Load();
private:
	std::string filePath;
	GLuint textureID;
};
#endif
