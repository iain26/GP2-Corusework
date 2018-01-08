#include "Mesh.h"
#include <vector>

// gets position, texture coordinate and normal for each vertice and stores them in a list
// adds each indice to a list 
//obsolete after loading from model file
void Mesh::InitialiseMesh(Vert* verts, unsigned int numVerts, unsigned int* ind, unsigned int numInd)
{
	IndModel m;

	for (unsigned int i = 0; i < numVerts; i++)
	{
		m.pos.push_back(*verts[i].GetPos());
		m.tC.push_back(*verts[i].GetTexCoord());
		m.n.push_back(*verts[i].GetNormal());
	}

	for (unsigned int i = 0; i < numInd; i++)
		m.ind.push_back(ind[i]);

	InitialiseModel(m);
}

void Mesh::InitialiseModel(const IndModel& m)
{
	//amount of indices
	indSize = m.ind.size();
	// generates a vertex array object 
	glGenVertexArrays(1, &vao); 
	glBindVertexArray(vao); 
	//generates vertex array buffer
	glGenBuffers(NumBuffer, vab); 
	// allocates memory for vertex array buffer elements
	// sends data of number of attributes in that element, memory pointer and location on GPU to store
	// enables attribute
	// index of generic attribute, size is number of components in attribute(pretty sure that means vec3 and vec2), type is float, it is not normalized, byte offset, point to first attribute
	// repeats the above for position, texture coordinates and normals
	glBindBuffer(GL_ARRAY_BUFFER, vab[PosVertBuffer]);
	glBufferData(GL_ARRAY_BUFFER, m.pos.size() * sizeof(m.pos[0]), &m.pos[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vab[TexcoordVertBuffer]); 
	glBufferData(GL_ARRAY_BUFFER, m.pos.size() * sizeof(m.tC[0]), &m.tC[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vab[NormalVertBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m.n[0]) * m.n.size(), &m.n[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// allocates memory for indices, and sends to gpu
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vab[IndexVertBuffer]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.ind.size() * sizeof(m.ind[0]), &m.ind[0], GL_STATIC_DRAW); 
	// unbind
	glBindVertexArray(0);
}

// constructor sets draw count to nothing
Mesh::Mesh()
{
		indSize = NULL;
}

// load model and run setup of model
void Mesh::ModelFileLoad(const std::string& file)
{
	IndModel m = OBJModel(file).ToIndexedModel();
	InitialiseModel(m);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao); // delete arrays
}

// draw model 
void Mesh::RenderModel()
{
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, indSize, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

// sphere used to calculate collision is set around object
void Mesh::SetBoundingSphere(glm::vec3 pos, float radius)
{
	boundSphere.SetPos(pos);
	boundSphere.SetRadius(radius);
}

