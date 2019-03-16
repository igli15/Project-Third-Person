#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include "mge/core/GameObject.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class CameraComponent;
class Camera : public GameObject
{
	public:
 		Camera();

		virtual ~Camera();

		void Load() override;

		CameraComponent* GetCameraComponent();
	private:
		CameraComponent* m_cameraComponent;

        Camera (const Camera&);
		Camera& operator= (const Camera&);
};

#endif // CAMERA_HPP
