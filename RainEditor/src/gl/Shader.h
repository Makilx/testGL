#pragma once
#include <glad/glad.h>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl {
	std::string ReadFile(const char* path);

	class Shader {
	public:
		Shader(GLenum type);
		Shader(GLenum type, std::string source);
		inline ~Shader() { Destroy(); }

		void Edit(std::string newSource);
		inline void Destroy() const { glDeleteShader(id); }
		inline GLuint GetID() const { return id; }

	private:
		GLuint id;
	};

	class ShaderProgram {
	public:
		ShaderProgram();
		ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
		~ShaderProgram();

		void Attach(Shader& shader);
		void Link();
		void Use();

		//#define __uniform(type, action) void Uniform(std::string name, type value) {\
		//									action;\
		//								}

		void Uniform(std::string name, GLfloat value) {
			Use();
			glUniform1f(GetUniformLocation(name), value);
		};

		void Uniform(std::string name, glm::vec2 value) {
			Use();
			glUniform2f(GetUniformLocation(name), value.x, value.y);
		};
		void Uniform(std::string name, glm::vec3 value) {
			Use();
			glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
		};
		void Uniform(std::string name, glm::vec4 value) {
			Use();
			glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.a);
		};
		void Uniform(std::string name, GLint value) {
			Use();
			glUniform1i(GetUniformLocation(name), value);
		};
		void Uniform(std::string name, GLuint value) {
			Use();
			glUniform1ui(GetUniformLocation(name), value);
		};
		void Uniform(std::string name, glm::mat4 value) {
			Use();
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
		};

	private:
		GLuint id;
		std::unordered_map<std::string, GLint> uniformCache;

		GLuint GetUniformLocation(std::string name) {
			// Find
			if (uniformCache.find(name) == uniformCache.end()) {
				GLint location = glGetUniformLocation(id, name.c_str());
				uniformCache.insert({ name, location });
				return location;
			}
			return uniformCache[name];
		}
	};
};