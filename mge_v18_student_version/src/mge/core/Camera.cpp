#include "glm.hpp"
#include "mge/core/Camera.hpp"

Camera::Camera( )
{
	_projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection() {
    return _projection;
}

