#include "Camera.h"
#include <algorithm>

float clamp(float x, float min, float max) {
	if (x > max) return max;
	if (x < min) return min;
	return x;
}

void Camera::Apply(ShaderProgram &shader, int windowWidth, int windowHeight, double deltaTime) {
	zoom = clamp(zoom, 0, HUGE);

	// Lerp position
	static glm::vec2 currentPosition;
	currentPosition = glm::mix(currentPosition, glm::vec2(position.x / 10, -position.y / 10), deltaTime * 33);
	static float currentZoom;
	currentZoom = glm::mix(currentZoom, zoom / 100.0f, (float)deltaTime * 33.0f);
	
	// Gen matrices
	glm::mat4 view(1);
	glm::mat4 ortho(1);

	// Translate view
	view = glm::translate(view, glm::vec3(-currentPosition.x, -currentPosition.y, 0.0f));
	view = glm::scale(view, glm::vec3(100.0f * currentZoom, 100.0f * currentZoom, 1));
	view = glm::rotate(view, glm::radians(rotation), glm::vec3(0, 0, 1));

	//float viewWidth = windowWidth / zoom;
	//float viewHeight = windowHeight / zoom;
	ortho = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
	//ortho = glm::ortho(0.0f, (float)viewWidth, (float)viewHeight, 0.0f, -1.0f, 1.0f);

	// Apply
	shader.Uniform("Camera", ortho * view);
}