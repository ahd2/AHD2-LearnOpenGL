#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	//可配置
	glm::vec3 Position;
	//只读
	glm::mat4 Matrix_VP;//相机VP矩阵
	//
	Camera();
	~Camera();

private:

};