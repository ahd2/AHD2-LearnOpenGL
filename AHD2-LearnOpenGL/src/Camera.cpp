#include "Camera.h"

Camera::Camera(glm::vec3& position, float fov, float nearPlane, float farPlane, int cameraPixelWidth, int cameraPixelHeight)
{
	Position = position;
	Fov = fov;
	NearPlane = nearPlane;
	FarPlane = farPlane;
	CameraPixelWidth = cameraPixelWidth;
	CameraPixelHeight = cameraPixelHeight;
	MouseSensitivity = 0.1;
	Yaw = 0.0f;
	Pitch = 0.0f;
	m_UpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	m_FrontDir = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{
	//暂时不需要写析构函数，因为没在堆内存分配资源
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + m_FrontDir, m_UpDir);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(Fov), (float)CameraPixelWidth / CameraPixelHeight, NearPlane, FarPlane);
}

void Camera::ProcessKeyboard(Camera_Movement direction, const float& deltaTime)
{
	float cameraSpeed = 10.0f;
	switch (direction)
	{
	case FORWARD:
		Position += m_FrontDir * cameraSpeed * deltaTime;
		break;
	case BACKWARD:
		Position -= m_FrontDir * cameraSpeed * deltaTime;
		break;
	case LEFT:
		Position -= m_RightDir * cameraSpeed * deltaTime;
		break;
	case RIGHT:
		Position += m_RightDir * cameraSpeed * deltaTime;
		break;
	case UP:
		Position += m_UpDir * cameraSpeed * deltaTime;
		break;
	case DOWN:
		Position -= m_UpDir * cameraSpeed * deltaTime;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(const float& xoffset, const float& yoffset, bool constrainPitch)
{
	Yaw += xoffset * MouseSensitivity;
	Pitch += yoffset * MouseSensitivity;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	m_FrontDir = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_RightDir = glm::normalize(glm::cross(m_FrontDir, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_UpDir = glm::normalize(glm::cross(m_RightDir, m_FrontDir));
}