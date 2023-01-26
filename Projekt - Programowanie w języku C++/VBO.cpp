#include "VBO.h"

struct Vertex
{
	float Position[3];
	float Color[3];
	float Texture[2];
};

VBO::VBO(size_t MaxVertexCount) // Function that creates a Vertex Buffer Object, based on declared size
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
}

void VBO::Bind() // Binding to use
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() // Unbinding to awoid any changes to it's structure
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() // Deleting VBO
{
	glDeleteBuffers(1, &ID);

}
