#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <stdexcept>

class EBO
{
	public:
		GLuint ID;
		EBO();

		void EBOUpdate(std::vector<GLuint> indices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
};

#endif
