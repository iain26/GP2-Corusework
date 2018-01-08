#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Cam.h"

class Shader
{
public:
	Shader(const std::string& file);
	void Bind();
	void UpdateShader(const Transform& transform, const Cam& camera);
	std::string Shader::ShaderLoad(const std::string& file);
	void Shader::ShaderErrorHandling(GLuint shader, GLuint flag, bool isProgram, const std::string& message);
	GLuint Shader::ShaderCreation(const std::string& text, unsigned int type);

    ~Shader();


protected:
private:
	static const unsigned int NumShade = 2; 

	enum
	{
		TransformUnif,
		NumUnifs
	};

	GLuint ShaderProgram;
	GLuint shaders[NumShade];
	GLuint uniforms[NumUnifs];
};
