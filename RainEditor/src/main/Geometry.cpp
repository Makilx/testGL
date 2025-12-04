#include "Geometry.h"
#include <iostream>

void Geometry::SetTile(int x, int y, TileType type) {
	// Set specific block
	x--;
	y--;
	if (x < 0 || y < 0 || x > width || y > height) return;
	tiles[y][x] = type;
	updateData = true;
}

void Geometry::Fill(int x0, int y0, int x1, int y1, TileType type) {
	// Fill a square of blocks
	x0--;
	x1--;
	y0--;
	y1--;
	if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0) return;
	if (x0 > width || y0 > height || x1 > width || y1 > height) return;

	// Fill
	short int xDirection = (x0 > x1) ? -1 : 1;
	short int yDirection = (y0 > y1) ? -1 : 1;

	for (int y = y0; (yDirection == -1 ? y > y1 : y < y1); y += yDirection) {
		for (int x = x0; (xDirection == -1 ? x > x1 : x < x1); x += xDirection) {
			tiles[y][x] = type;
		}
	}
	updateData = true;
}

void Geometry::Resize(int width, int height) {
	// Resize board
	this->width = width;
	this->height = height;

	tiles.resize(height);
	for (auto& tileSet : tiles)
		tileSet.resize(width, TileType::Air);

	// Update data
	UpdateData();
}

void Geometry::Draw(Camera& camera, GLFWwindow *window) {
	// Load data
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	static double lastTime = 0;
	double currentTime = glfwGetTime();
	double delta = currentTime - lastTime;
	lastTime = currentTime;

	shaders.Use();
	array.Bind();

	// Activate camera
	camera.Apply(shaders, width, height, delta);

	// Use texure
	geometrySpriteSheet.Use(shaders, 0);

	// Update Data
	if (updateData) {
		std::cout << "DataUpdated!" << std::endl;
		UpdateData();
		updateData = false;
	}

	// Update buffers
	if (updateBuffers) {
		std::cout << "BuffersUpdated!" << std::endl;
		VertexArrayLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		
		vbo.Bind();
		layout.Apply();
		ibo.Bind();

		updateBuffers = false;
	}

	// Draw
	//glDrawElements(GL_LINE_LOOP, indicesCount, GL_UNSIGNED_INT, NULL);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}

TexCoords getTileTexCoords(TileType type, Texture& tex) {
	switch (type) {
	default:
	case TileType::Solid: return tex.tileGetCoords(0, 0, 25);
	case TileType::Slope: return tex.tileGetCoords(1, 0, 25);
	}
}

void Geometry::UpdateData() {
	// Load current information about the grid
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Check block type
			if (tiles[y][x] == TileType::Air) continue;

			// Fill all the needed data
			// compute start index for this quad
			GLuint start = static_cast<GLuint>(vertices.size());

			// Calculate texture coordinates
			TexCoords coords = getTileTexCoords(tiles[y][x], geometrySpriteSheet);

			// Define quad vertices (positions + UVs). Adjust as needed.
			vertices.push_back({ (float)x + 0.0f, (float)y + 1.0f,  coords.u0, coords.v1 });
			vertices.push_back({ (float)x + 0.0f, (float)y + 0.0f,  coords.u0, coords.v0 });
			vertices.push_back({ (float)x + 1.0f, (float)y + 0.0f,  coords.u1, coords.v0 });
			vertices.push_back({ (float)x + 1.0f, (float)y + 1.0f,  coords.u1, coords.v1 });

			// two triangles: (start, start+1, start+2), (start, start+2, start+3)
			indices.push_back(start + 0);
			indices.push_back(start + 1);
			indices.push_back(start + 2);

			indices.push_back(start + 0);
			indices.push_back(start + 2);
			indices.push_back(start + 3);
		}
	}

	// Set buffer datas
	indicesCount = indices.size();
	vbo.Data(vertices.data(), vertices.size() * sizeof(Vertex));
	ibo.Data(indices.data(), indices.size() * sizeof(GLuint));
	updateBuffers = true;
}