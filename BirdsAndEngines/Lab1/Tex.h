#pragma once
#include <string>
#include <GL\glew.h>

class Tex
{
public:
	Tex(const std::string& file);

	void Bind(unsigned int unit); // bind upto 32 textures

	~Tex();

protected:
private:

	GLuint handleTexture;
};

