#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	//������
	glm::vec3 Position;
	//ֻ��
	glm::mat4 Matrix_VP;//���VP����
	//
	Camera();
	~Camera();

private:

};