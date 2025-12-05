#pragma once
#include "gl/Buffer.h"
#include <vector>

namespace gl {
	struct VAElement {
		unsigned int count;
		GLenum type;
		bool normalized;
	};

	class VertexArrayLayout {
	public:
		void Apply() {
			GLsizeiptr offset = 0;

			for (int i = 0; i < elements.size(); i++) {
				VAElement& e = elements[i];
				glVertexAttribPointer(i, e.count, e.type, (e.normalized) ? GL_TRUE : GL_FALSE, stride, (const void*)offset);
				glEnableVertexAttribArray(i);
				offset += GetTypeSize(e.type) * e.count;
			}
		}

		template<typename T>
		void Push(unsigned int count, bool normalized = false);

		//#define __pushdefinition(type1, type2)	template<>\
		//										void Push<type1>(unsigned int count, bool normalized) {\
		//											elements.push_back({count, type2, normalized});\
		//											stride += GetTypeSize(type2) * count;\
		//										}

		template<>
		void Push<float>(unsigned int count, bool normalized) {
			elements.push_back({ count, GL_FLOAT, normalized });
			stride += GetTypeSize(GL_FLOAT) * count;
		};
		template<>
		void Push<int>(unsigned int count, bool normalized) {
			elements.push_back({ count, GL_INT, normalized });
			stride += GetTypeSize(GL_INT) * count;
		};
		template<>
		void Push<unsigned int>(unsigned int count, bool normalized) {
			elements.push_back({ count, GL_UNSIGNED_INT, normalized });
			stride += GetTypeSize(GL_UNSIGNED_INT) * count;
		};

	private:
		std::vector<VAElement> elements;
		GLsizeiptr stride = 0;

#define __returndefinition(type1, type2) case type1: return sizeof(type2)
		GLsizeiptr GetTypeSize(GLenum type) {
			switch (type) {
				__returndefinition(GL_FLOAT, GLfloat);
				__returndefinition(GL_INT, GLint);
				__returndefinition(GL_UNSIGNED_INT, GLuint);
			}
			return 0;
		}
	};

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

	private:
		GLuint id;
	};
}