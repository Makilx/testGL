#include "gl/Buffer.h"
using namespace gl;

Buffer::Buffer(GLenum type) {
	this->type = type;
	glCreateBuffers(1, &id);
}

Buffer::Buffer(GLenum type, const void* data, GLsizeiptr size, GLenum usage) {
	this->type = type;
	glCreateBuffers(1, &id);
	Data(data, size, usage);
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &id);
}

void Buffer::Bind() {
	glBindBuffer(type, id);
}

void Buffer::Unbind() {
	glBindBuffer(type, 0);
}

void Buffer::Data(const void* data, GLsizeiptr size, GLenum usage) {
	glNamedBufferData(id, size, data, usage);
}

void Buffer::SubData(GLsizeiptr offset, const void* data, GLsizeiptr size) {
	glNamedBufferSubData(id, offset, size, data);
}