#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//����ƶ�����
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	//������
	glm::vec3 Position;
	float MouseSensitivity;
	float Yaw;
	float Pitch;
	//ֻ��
	glm::mat4 Matrix_VP;//���VP����
	//
	Camera(glm::vec3& position);
	~Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction,const float& deltaTime);
	void ProcessMouseMovement(const float& xoffset, const float& yoffset, bool constrainPitch = true);

private:
	glm::vec3 m_UpDir;
	glm::vec3 m_FrontDir;
	glm::vec3 m_RightDir;
	void updateCameraVectors();
};