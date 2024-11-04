#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//相机移动方向
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	//可配置
	glm::vec3 Position;
	//只读
	glm::mat4 Matrix_VP;//相机VP矩阵
	//
	Camera(glm::vec3& position);
	~Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

private:
	glm::vec3 m_UpDir;
	glm::vec3 m_FrontDir;
};