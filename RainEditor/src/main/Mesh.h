#pragma once
#include <gl/VertexArray.h>

class Mesh {
public:
	gl::VertexArrayLayout layout;

	Mesh(GLenum usage = GL_STATIC_DRAW);
	Mesh(GLfloat* vertices, GLsizeiptr vSize, GLenum usage = GL_STATIC_DRAW);
	Mesh(GLfloat* vertices, GLsizeiptr vSize, GLuint* indices, GLsizeiptr iSize, GLenum usage = GL_STATIC_DRAW);

	void VerticesData(GLfloat* vertices, GLsizeiptr vSize);
	void VerticesSubData(GLsizeiptr offset, GLfloat* vertices, GLsizeiptr vSize);
	void IndicesData(GLuint* indices, GLsizeiptr iSize);
	void IndicesSubData(GLsizeiptr offset, GLuint* indices, GLsizeiptr iSize);

	void Draw(GLenum drawType = GL_TRIANGLES);

private:
	// Draw data
	gl::VertexArray array;
	gl::Buffer vbo, ibo;

	// Data
	GLenum drawType;
	unsigned int indicesCount = 0;
	bool updateBuffers = false;
};