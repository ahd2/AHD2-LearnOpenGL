#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//����ƶ�����
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	//������
	glm::vec3 Position;
	//ֻ��
	glm::mat4 Matrix_VP;//���VP����
	//
	Camera(glm::vec3& position);
	~Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

private:
	glm::vec3 m_UpDir;
	glm::vec3 m_FrontDir;
};