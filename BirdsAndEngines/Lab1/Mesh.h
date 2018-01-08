#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vert
{
public:
	Vert(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct BoundingSphere
{
public:

	BoundingSphere(){}
	BoundingSphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
		this->radius = radius;
	}

	glm::vec3 GetSpherePos() { return pos; }
	float GetSphereRadius() { return radius; }
	void SetPos(glm::vec3 pos) { this->pos = pos; }
	void SetRadius(float radius){ this->radius = radius; }

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void RenderModel();
	void InitialiseMesh(Vert* verts, unsigned int numVerts, unsigned int* ind, unsigned int numInd);
	void ModelFileLoad(const std::string& file);
	void InitialiseModel(const IndModel& m);
	void SetBoundingSphere(glm::vec3 pos, float radius);
	glm::vec3 getBoundingSpherePos() { return boundSphere.GetSpherePos(); }
	float getBoundingSphereRadius() { return boundSphere.GetSphereRadius(); }

private:

	enum
	{
		PosVertBuffer,
		TexcoordVertBuffer,
		NormalVertBuffer,
		IndexVertBuffer,
		NumBuffer
	};

	BoundingSphere boundSphere;
	GLuint vao;
	GLuint vab[NumBuffer];
	unsigned int indSize;
};