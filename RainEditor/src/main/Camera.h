#pragma once
#include <gl/Shader.h>
#include <glfw/glfw3.h>

class Camera {
public:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	float rotation = 0.0f;
	float zoom = 1.0f;

	void Apply(ShaderProgram& shader, int windowWidth, int windowHeight, double deltaTime);
};