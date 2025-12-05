#pragma once
#include <gl/Shader.h>

namespace gl {
	enum class PixelFormat {
		RGB,
		RGBNormalized
	};

	struct TexCoords {
		float u0;		// Left
		float u1;		// Right
		float v0;		// Bottom
		float v1;		// Top
	};

	class Texture {
	public:
		Texture(std::string filePath);
		~Texture();

		void Use(ShaderProgram& shader, GLint slot = 0);

		/// <summary>
		/// Use this after setup to free image data from CPU memory
		/// </summary>
		void Free();

		/// <summary>
		/// Only works before Free() is called
		/// </summary>
		/// <returns></returns>
		glm::vec4 GetPixel(int x, int y, PixelFormat format = PixelFormat::RGB) const {
			int index = (y * width + x) * 4;

			switch (format) {
			case PixelFormat::RGB:
				return glm::vec4(
					float(data[index]),
					float(data[index + 1]),
					float(data[index + 2]),
					1.0f
				);

			case PixelFormat::RGBNormalized:
				return glm::vec4(
					float(data[index]) / 255.0f,
					float(data[index + 1]) / 255.0f,
					float(data[index + 2]) / 255.0f,
					1.0f
				);
			}
		}

		glm::vec2 GetSize() const {
			return glm::vec2(float(width), float(height));
		}

		TexCoords TileGetCoords(int x, int y, int tileSize) {
			float pointWidth = float(tileSize) / float(width);
			float pointHeight = float(tileSize) / float(height);

			TexCoords coords;
			coords.u0 = pointWidth * x;           // left
			coords.u1 = pointWidth * (x + 1);     // right
			coords.v0 = pointHeight * y;          // bottom
			coords.v1 = pointHeight * (y + 1);    // top

			return coords;
		}

	private:
		GLuint id;
		int width = 0, height = 0;
		unsigned char* data;
	};
}