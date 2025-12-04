#include "gl/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string ReadFile(const char* path) {
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	// Fail
	std::cerr << "ERROR -> FAILED TO LOAD FILE AT: " << path << std::endl;
	return "";
}

Shader::Shader(GLenum type) {
	id = glCreateShader(type);
}

Shader::Shader(GLenum type, std::string source) {
	id = glCreateShader(type);
	Edit(source);
}

void Shader::Edit(std::string source) {
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	// Get errors
	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint logLen = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);

		std::string infoLog;
		infoLog.resize(logLen);
		glGetShaderInfoLog(id, logLen, nullptr, (GLchar*)infoLog.data());

		std::cerr << "ERROR -> SHADER -> COMPILATION FAILED\n" << infoLog << std::endl;
	}
}

ShaderProgram::ShaderProgram() {
	id = glCreateProgram();
}

ShaderProgram::ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource) {
	id = glCreateProgram();

	// Create 2 shaders
	Shader vShader(GL_VERTEX_SHADER, vertexShaderSource);
	Shader fShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	Attach(vShader);
	Attach(fShader);
	Link();
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(id);
}

void ShaderProgram::Attach(Shader &shader) {
	glAttachShader(id, shader.GetID());
}

void ShaderProgram::Link() {
	glLinkProgram(id);
}

void ShaderProgram::Use() {
	glUseProgram(id);
}