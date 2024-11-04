#include "Camera.h"

Camera::Camera(glm::vec3& position)
{
	Position = position;
	m_UpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	m_FrontDir = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + m_FrontDir, m_UpDir);
}

void Camera::ProcessKeyboard(Camera_Movement direction, const float& deltaTime)
{
	float cameraSpeed = 10.0f;
	switch (direction)
	{
	case FORWARD:
		Position.z -= cameraSpeed * deltaTime;
		break;
	case BACKWARD:
		Position.z += cameraSpeed * deltaTime;
		break;
	case LEFT:
		Position.x -= cameraSpeed * deltaTime;
		break;
	case RIGHT:
		Position.x += cameraSpeed * deltaTime;
		break;
	case UP:
		Position.y += cameraSpeed * deltaTime;
		break;
	case DOWN:
		Position.y -= cameraSpeed * deltaTime;
		break;
	default:
		break;
	}
}
