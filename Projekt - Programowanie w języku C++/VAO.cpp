#include"VAO.h"


VAO::VAO() // Constructor that generates a Vertex Array Object ID
{
	glGenVertexArrays(1, &ID);
}


void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) // Links a VBO Attribute such as a position or color to the VAO
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}


void VAO::Bind() // Binds the VAO
{
	glBindVertexArray(ID);
}


void VAO::Unbind() // Unbinds the VAO
{
	glBindVertexArray(0);
}


void VAO::Delete() // Deletes the VAO
{
	glDeleteVertexArrays(1, &ID);
}