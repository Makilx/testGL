#pragma once
#include <glad/glad.h>

class Buffer {
public:
	Buffer(GLenum type);
	Buffer(GLenum type, const void *data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	~Buffer();

	void Bind();
	void Unbind();
	void Data(const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	void SubData(GLsizeiptr offset, const void* data, GLsizeiptr size);

private:
	GLuint id;
	GLenum type;
};