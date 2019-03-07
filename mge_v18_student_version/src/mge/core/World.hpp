#ifndef WORLD_HPP
#define WORLD_HPP

#include "mge/core/GameObject.hpp"
#include "mge\components\CanvasComponent.h"

class Camera;
class Light;
class LightComponent;
class CameraComponent;

class World : public GameObject
{
	public:
        World();
		virtual void Initialize() ;
		void setMainCamera (CameraComponent* pCamera);
		CameraComponent* getMainCamera();


        //only used internally, do not use from outside
        void registerLight (LightComponent* pLight);
        void unregisterLight (LightComponent* pLight);

		void MarkAllGameObjectForDeletion();

        LightComponent* getLightAt (int pIndex);
        int getLightCount();

		template <typename T>
		T* Instantiate()
		{
			T* gameObject = new T;
			add(gameObject);

			gameObject->Load();
			gameObject->Awake();
			gameObject->Start();
			
			return gameObject;
		}

		void ClearMarkedGameObject();
		void InnerDestroy(GameObject* object);
		void SetCanvas(CanvasComponent* canvas);

		void InnerRegisterLightByType(LightComponent* light);
		void InnerDeRegisterLightByType(LightComponent* light);

		CanvasComponent* GetCanvasComponent();
	private:

		CanvasComponent * m_mainCanvas = nullptr;
	    Camera* _mainCamera;
		CameraComponent* m_mainCameraComponent;
	    std::vector<LightComponent*> _lights;

		std::vector<LightComponent*> m_pointLights;
		std::vector<LightComponent*> m_spotLights;
		std::vector<LightComponent*> m_dirLights;

        World(const World&);
        World& operator=(const World&);
};


#endif // WORLD_HPP
