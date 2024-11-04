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

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
}
