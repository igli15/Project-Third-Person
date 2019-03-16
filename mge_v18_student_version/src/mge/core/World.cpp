#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/components/CameraComponent.h"

#include "Tweener.h"

World::World()
{
	_world = this;
}

World::~World()
{
	/*
	for (int i = _children.size() - 1; i >= 0; --i)
	{
		_children[i]->OnDestroy();
		for (int j = _children[i]->getChildCount() - 1; j >= 0; --j)
		{
			_children[i]->getChildAt(j)->OnDestroy();
		}
	}
	*/
}

void World::Initialize()
{
}

void World::setMainCamera (CameraComponent* pCamera) {
    if (pCamera != NULL) m_mainCameraComponent = pCamera;
}


CameraComponent* World::getMainCamera () {
    return m_mainCameraComponent;
}


void World::registerLight (LightComponent* pLight) 
{
    std::cout << "Registering light " << pLight->GetGameObject()->getName() << std::endl;
    _lights.push_back(pLight);

	InnerRegisterLightByType(pLight);
}

void World::unregisterLight (LightComponent* pLight) {
    std::cout << "Unregistering light " << pLight->GetGameObject()->getName() << std::endl;
	if (_lights.size() == 0) return;
    _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());

	InnerDeRegisterLightByType(pLight);
}

void World::MarkAllGameObjectForDeletion()
{
	for (int i = _children.size() - 1; i >= 0; --i)
	{
		_children[i]->Destroy();
		for (int j = _children[i]->getChildCount() - 1; j >= 0; --j)
		{
			_children[i]->getChildAt(j)->Destroy();
		}
	}
}

LightComponent* World::getLightAt (int pIndex) {
    return _lights[pIndex];
}

int World::getLightCount() {
    return _lights.size();
}

void World::ClearMarkedGameObject()
{
	for (int i = _children.size() - 1; i >= 0; --i)
	{

		for (int j = _children[i]->getChildCount() - 1; j >= 0; --j)
		{
			if (_children[i]->getChildAt(j)->IsMarkedForDestruction())
			{
				InnerDestroy(_children[i]->getChildAt(j));
			}
		}

		if (_children[i]->IsMarkedForDestruction())
		{
			InnerDestroy(_children[i]);
		}
		
	}

}

void World::InnerDestroy(GameObject * object)
{
	remove(object);
	delete object;
}

void World::SetCanvas(CanvasComponent * canvas)
{
	m_mainCanvas = canvas;
}

void World::InnerRegisterLightByType(LightComponent * pLight)
{
	std::string s;
	if (pLight->GetType() == LightType::POINT)
	{
		m_pointLights.push_back(pLight);
		s = "pointLight[" + std::to_string(m_pointLights.size() - 1) + "].";
	}
	else if (pLight->GetType() == LightType::DIRECTIONAL)
	{
		m_dirLights.push_back(pLight);
		s = "directionalLight[" + std::to_string(m_dirLights.size() - 1) + "].";;
	}
	else if (pLight->GetType() == LightType::SPOTLIGHT)
	{
		m_spotLights.push_back(pLight);
		s = "spotLight[" + std::to_string(m_spotLights.size() - 1) + "].";
	}

	std::cout << s << std::endl;
	pLight->SetMaterialIndexString(s);
	pLight->AssignUnifromLocation();
}

void World::InnerDeRegisterLightByType(LightComponent * pLight)
{
	if (pLight->GetType() == LightType::POINT)
	{
		m_pointLights.erase(std::remove(m_pointLights.begin(), m_pointLights.end(), pLight), m_pointLights.end());
		for (size_t i = 0; i < m_pointLights.size(); i++)
		{
			m_pointLights[i]->SetMaterialIndexString("pointLight[" + std::to_string(i) + "].");
			std::cout << "pointLight[" + std::to_string(m_pointLights.size() - 1) + "]." << std::endl;
		}
	}
	else if (pLight->GetType() == LightType::DIRECTIONAL)
	{
		m_dirLights.erase(std::remove(m_dirLights.begin(), m_dirLights.end(), pLight), m_dirLights.end());
		for (size_t i = 0; i < m_dirLights.size(); i++)
		{
			m_dirLights[i]->SetMaterialIndexString("directionalLight[" + std::to_string(i) + "].");
			std::cout << "directionalLight[" + std::to_string(m_pointLights.size() - 1) + "]." << std::endl;
		}
	}
	else if (pLight->GetType() == LightType::SPOTLIGHT)
	{
		m_spotLights.erase(std::remove(m_spotLights.begin(), m_spotLights.end(), pLight), m_spotLights.end());
		for (size_t i = 0; i < m_spotLights.size(); i++)
		{
			m_spotLights[i]->SetMaterialIndexString("spotLight[" + std::to_string(i) + "].");
			std::cout << "spotLight[" + std::to_string(m_pointLights.size() - 1) + "]." << std::endl;
		}
	}

	pLight->AssignUnifromLocation();
}

CanvasComponent* World::GetCanvasComponent()
{
	return m_mainCanvas;
}