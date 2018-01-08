#include "Tex.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Tex::Tex(const std::string& file)
{
	// width, height and number of components on an image
	int widthofTex, heightOfTex, numComp;
	// loads texture from file and returns if texture load failed
	unsigned char* data = stbi_load((file).c_str(), &widthofTex, &heightOfTex, &numComp, 4); 
	if (data == NULL)
	{
		std::cerr << "texture load failed" << file << std::endl;
	}
	// num of textures to be generated and the array to assign twxtures to
	glGenTextures(1, &handleTexture); 
	glBindTexture(GL_TEXTURE_2D, handleTexture);
	// wrap texture so that texture repeats after width and height exceeded
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthofTex, heightOfTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 

	stbi_image_free(data);
}

Tex::~Tex()
{
	glDeleteTextures(1, &handleTexture);
}

void Tex::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); 
	// sets active texture and type of texture that is
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, handleTexture);
}
