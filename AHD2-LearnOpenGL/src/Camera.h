#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//相机移动方向
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
	//可配置
	//渲染参数
	glm::vec3 Position;
	float Fov;
	float NearPlane;
	float FarPlane;
	int CameraPixelHeight;//相机渲染宽高（暂时用屏幕宽高代替。后续通过这个可以决定渲染RT的大小。
	int CameraPixelWidth;
	//相机控制
	float MouseSensitivity;
	float Yaw;
	float Pitch;
	//只读
	glm::mat4 Matrix_VP;//相机VP矩阵
	//
	Camera(glm::vec3& position, float fov, float nearPlane, float farPlane, int cameraPixelWidth, int cameraPixelHeight);
	~Camera();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void ProcessKeyboard(Camera_Movement direction,const float& deltaTime);
	void ProcessMouseMovement(const float& xoffset, const float& yoffset, bool constrainPitch = true);

private:
	glm::vec3 m_UpDir;
	glm::vec3 m_FrontDir;
	glm::vec3 m_RightDir;
	void updateCameraVectors();
};