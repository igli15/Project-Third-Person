#include "glm.hpp"
#include "mge/core/Camera.hpp"
#include "../components/CameraComponent.h"

Camera::Camera( )
{
	
}

Camera::~Camera()
{
	//dtor
}

void Camera::Load()
{
	m_cameraComponent = AddComponent<CameraComponent>();
}

CameraComponent * Camera::GetCameraComponent()
{
	return m_cameraComponent;
}


