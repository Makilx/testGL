#pragma once
#include <gl/Shader.h>

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

	TexCoords tileGetCoords(int x, int y, int tileSize) {
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
};