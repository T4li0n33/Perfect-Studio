#include "EBO.h"

EBO::EBO()
{
	glGenBuffers(1, &ID);
}

void EBO::EBOUpdate(std::vector<GLuint> indices, GLsizeiptr size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	if (indices.empty()) {
		throw std::runtime_error("Index vector is empty!");
	}
	size_t size_b = indices.size() * sizeof(GLuint);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_b, &indices.front(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);

}