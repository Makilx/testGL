#pragma once
#include <gl/Shader.h>
#include <type/CFrame.h>
#include <glfw/glfw3.h>

class Camera {
public:
	CFrame cframe;
	float fieldOfView		= 60.0f;
	bool orthographicCamera = false;

	void Activate(gl::ShaderProgram& shader, GLFWwindow* window) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glm::mat4 proj(1);

		if (orthographicCamera)
			proj = glm::perspective(fieldOfView, (float)(width/height), 0.0f, 100.0f);
		else
			proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

		// Use shaders
		shader.Uniform("Camera", proj * cframe.toMat4());
	}
};