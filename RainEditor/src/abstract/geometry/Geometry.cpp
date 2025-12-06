#include "Geometry.h"

void Geometry::Load(std::string path, std::string fileName) {
    // Clear data
    Unload();

    // Load 2 files
    // 1. The actual map / geometry
    // 2. The map collisions
    geometryTex = gl::Texture(path + "\\" + fileName + "_map.jpg");
    gl::Texture collisionTexture(path + "\\" + fileName + "_col.jpg");

    // load collision
    glm::vec2 size = collisionTexture.GetSize();

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            geometry[y][x] = (collisionTexture.GetPixel(x, y, gl::PixelFormat::RGB) == glm::vec4(0));
        }
    }
}

void Geometry::Unload() {

}

void Geometry::Draw() {

}

bool Geometry::CheckCollision(int x, int y) {
    return false;
}
