#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CFrame {
public:
	glm::vec3 position;
	glm::mat3 rotation;

	// Constructors
	CFrame(const glm::vec3& pos, const glm::mat3& rot)		: position(pos), rotation(rot) {}
	CFrame(const glm::vec3& pos)							: position(pos), rotation(glm::mat3(0)) {}
	CFrame()												: position(glm::vec3(0)), rotation(glm::mat3(0)) {}

	static CFrame fromEulerAnglesXYZ(float x, float y, float z) {
		glm::mat4 rx = glm::rotate(glm::mat4(1), glm::radians(x), glm::vec3(1, 0, 0));
		glm::mat4 ry = glm::rotate(glm::mat4(1), glm::radians(y), glm::vec3(0, 1, 0));
		glm::mat4 rz = glm::rotate(glm::mat4(1), glm::radians(z), glm::vec3(0, 0, 1));

		return CFrame(glm::vec3(0), rz * ry * rx);
	}

	static CFrame lookAt(glm::vec3 from, glm::vec3 to) {
		glm::vec3 forward = glm::normalize(to - from);
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
		glm::vec3 up = glm::cross(forward, right);

		return CFrame(from, glm::mat3(right, up, forward));
	}

	static CFrame fromMatrix(glm::mat4& matrix) {
		return CFrame(glm::vec3(matrix[3]), glm::mat3(matrix));
	}

	// Conversions

	glm::mat4 toMat4() {
		return glm::mat4(
			glm::vec4(rotation[0], 0.0f),
			glm::vec4(rotation[1], 0.0f),
			glm::vec4(rotation[2], 0.0f),
			glm::vec4(position, 1.0f)
		);
	}

	// Methods

	CFrame operator*(const CFrame& other) const {
		return CFrame(
			(position + rotation * other.position), // Pos
			(rotation * other.rotation)	// Rot
		);
	}

	CFrame inverse() const {
		glm::mat3 invRot = glm::transpose(rotation); // orthonormal
		glm::vec3 invPos = -(invRot * position);
		return CFrame(invPos, invRot);
	}
	
	glm::vec3 pointToWorld(const glm::vec3& p) const {
		return position + rotation * p;
	}

	glm::vec3 pointToLocal(const glm::vec3& p) const {
		return glm::transpose(rotation) * (p - position);
	}
};