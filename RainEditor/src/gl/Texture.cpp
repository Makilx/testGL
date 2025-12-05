#include "Texture.h"
#include <stb/stb_image.h>
#include <string>
using namespace gl;

Texture::Texture(std::string filePath) {
	stbi_set_flip_vertically_on_load(true);

	// Find file
	const char* path = filePath.c_str();
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	GLenum imageType = (channels == 3) ? GL_RGB : GL_RGBA;

	if (!data) {
		std::cout << "ERROR -> TEXTURE -> FAILED TO LOAD TEXTURE AT: " << filePath << std::endl;
	}

	// Load texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, imageType, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->width = width;
	this->height = height;
	this->data = data;
}

Texture::~Texture() {
	if (data) Free();
	glDeleteTextures(1, &id);
}

void Texture::Use(ShaderProgram& shader, GLint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);

	std::string name = "Texture" + std::to_string(slot);
	shader.Uniform(name, slot);
}

void Texture::Free() {
	stbi_image_free(data);
}