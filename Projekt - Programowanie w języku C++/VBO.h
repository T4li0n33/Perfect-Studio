#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>


class VBO
{
public:

	GLuint ID;
	VBO(size_t MaxVertexCount);

	void Bind();
	void Unbind();
	void Delete();

};


#endif