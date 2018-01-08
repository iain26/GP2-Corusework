#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filename)
{
	//create shader program and each of its components vertex and fragment shader
	ShaderProgram = glCreateProgram();
	shaders[0] = ShaderCreation(ShaderLoad(filename + ".vert"), GL_VERTEX_SHADER); 
	shaders[1] = ShaderCreation(ShaderLoad(filename + ".frag"), GL_FRAGMENT_SHADER);

	// add shaders to program
	for (unsigned int i = 0; i < NumShade; i++)
	{
		glAttachShader(ShaderProgram, shaders[i]);
	}
	// link positons, normals and texture coordinates assigned to shader program
	glBindAttribLocation(ShaderProgram, 0, "position");
	glBindAttribLocation(ShaderProgram, 1, "normal"); 
	glBindAttribLocation(ShaderProgram, 2, "texCoord");
	// create executable and return if the link to shader program was successful
	glLinkProgram(ShaderProgram);
	ShaderErrorHandling(ShaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed");
	// validates whether executables are contained in shader program
	glValidateProgram(ShaderProgram);
	ShaderErrorHandling(ShaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
	// get transform uniform from shader program
	uniforms[TransformUnif] = glGetUniformLocation(ShaderProgram, "transform");
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NumShade; i++)
	{
		glDetachShader(ShaderProgram, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(ShaderProgram);
}

// makes object part of the rendering state
void Shader::Bind()
{
	glUseProgram(ShaderProgram);
}

void Shader::UpdateShader(const Transform& transform, const Cam& camera)
{
	// get matrix of view and transform of object
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	// passes uniform location, matrices to be modified, column major order and the value to set uniform to
	glUniformMatrix4fv(uniforms[TransformUnif], 1, GLU_FALSE, &mvp[0][0]);
}

// creates individual shaders to be used
GLuint Shader::ShaderCreation(const std::string& text, unsigned int type)
{
	// initialises shader of a certain type i.e. fragment or vertex
	GLuint shaderToCreate = glCreateShader(type);
	// checks if shader exists
	if (shaderToCreate == 0)
		std::cerr << "Error type creation failed " << type << std::endl;
	
	const GLchar* stringS[1];
	stringS[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();
	// give opengl the source file and then run it
	glShaderSource(shaderToCreate, 1, stringS, lengths); 
	glCompileShader(shaderToCreate);
	// checks if compiled
	ShaderErrorHandling(shaderToCreate, GL_COMPILE_STATUS, false, "Error compiling shader!"); 
	// then shader has been created
	return shaderToCreate;
}

// finds shader file in folder
std::string Shader::ShaderLoad(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

// returns error messages
void Shader::ShaderErrorHandling(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

