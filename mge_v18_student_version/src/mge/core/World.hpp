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

        LightComponent* getLightAt (int pIndex);
        int getLightCount();

		template <typename T>
		T* Instantiate()
		{
			T* gameObject = new T;
		
			gameObject->Load();
			gameObject->Awake();
			gameObject->Start();
			add(gameObject);
			return gameObject;
		}

		void ClearMarkedGameObject();
		void InnerDestroy(GameObject* object);
		void SetCanvas(CanvasComponent* canvas);
		CanvasComponent* GetCanvasComponent();
	private:

		CanvasComponent * m_mainCanvas = nullptr;
	    Camera* _mainCamera;
		CameraComponent* m_mainCameraComponent;
	    std::vector<LightComponent*> _lights;

        World(const World&);
        World& operator=(const World&);
};


#endif // WORLD_HPP
