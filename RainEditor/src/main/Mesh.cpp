#include "Mesh.h"

Mesh::Mesh(GLenum usage) 
	: vbo(GL_ARRAY_BUFFER), ibo(GL_ELEMENT_ARRAY_BUFFER), drawType(usage) {
}

Mesh::Mesh(GLfloat* vertices, GLsizeiptr vSize, GLenum usage) 
	: vbo(GL_ARRAY_BUFFER, vertices, vSize, usage), ibo(GL_ELEMENT_ARRAY_BUFFER), drawType(usage) {
}

Mesh::Mesh(GLfloat* vertices, GLsizeiptr vSize, GLuint* indices, GLsizeiptr iSize, GLenum usage)
	: vbo(GL_ARRAY_BUFFER, vertices, vSize, usage), ibo(GL_ELEMENT_ARRAY_BUFFER, indices, iSize, usage), drawType(usage) {
	indicesCount = iSize / sizeof(GLuint);
}

void Mesh::VerticesData(GLfloat* vertices, GLsizeiptr vSize) {
	vbo.Data(vertices, vSize);
	updateBuffers = true;
}

void Mesh::VerticesSubData(GLsizeiptr offset, GLfloat* vertices, GLsizeiptr vSize) {
	vbo.SubData(offset, vertices, vSize);
	updateBuffers = true;
}

void Mesh::IndicesData(GLuint* indices, GLsizeiptr iSize) {
	ibo.Data(indices, iSize);
	updateBuffers = true;
	indicesCount = iSize / sizeof(GLuint);
}

void Mesh::IndicesSubData(GLsizeiptr offset, GLuint* indices, GLsizeiptr iSize) {
	ibo.SubData(offset, indices, iSize);
	updateBuffers = true;
}

void Mesh::Draw(GLenum drawType) {
	if (indicesCount == 0) return;
	array.Bind();

	// Update
	if (updateBuffers) {
		vbo.Bind();
		layout.Apply();
		ibo.Bind();
		updateBuffers = false;
	}

	// Draw
	glDrawElements(drawType, indicesCount, GL_UNSIGNED_INT, NULL);
}