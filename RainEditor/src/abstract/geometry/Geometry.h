#pragma once
#include <gl/Texture.h>
#include <abstract/Mesh.h>
#include <string>
#include <vector>

static class Geometry {
public:
	static void Load(std::string path, std::string fileName);
	static void Unload();
	static void Draw();
	static bool CheckCollision(int x, int y);

private:
	static gl::Texture& geometryTex;
	static Mesh& geometryMesh;

	static std::vector<std::vector<unsigned int>> geometry;
	static int width, height;
};