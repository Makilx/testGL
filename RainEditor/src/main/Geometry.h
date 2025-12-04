#pragma once
#include <gl/VertexArray.h>
#include <gl/Texture.h>
#include <glfw/glfw3.h>

enum class TileType : unsigned int {
	Air = 0,
	Solid,
	Slope
};

struct Vertex {
	GLfloat x, y;
	GLfloat texX, texY;
};

class Geometry {
public:
	Geometry() : array(), vbo(GL_ARRAY_BUFFER), ibo(GL_ELEMENT_ARRAY_BUFFER), geometrySpriteSheet("resources\\GeometrySheet.png") {}

	void SetTile(int x, int y, TileType type);
	void Fill(int x0, int y0, int x1, int y1, TileType type);
	void Resize(int width, int height);

	void Draw(ShaderProgram& shader);

private:
	VertexArray array;
	Buffer vbo;
	Buffer ibo;
	Texture geometrySpriteSheet;

	bool updateBuffers = true;
	bool updateData = false;

	std::vector<std::vector<TileType>> tiles;
	unsigned int indicesCount = 0;

	int width = 0, height = 0;

	void UpdateData();
	
};