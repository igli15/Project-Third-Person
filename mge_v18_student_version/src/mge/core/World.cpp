#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/components/CameraComponent.h"

World::World()
{
	_world = this;
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


void World::registerLight (LightComponent* pLight) {
    std::cout << "Registering light " << pLight->GetGameObject()->getName() << std::endl;
    _lights.push_back(pLight);
}

void World::unregisterLight (LightComponent* pLight) {
    std::cout << "Unregistering light " << pLight->GetGameObject()->getName() << std::endl;
	if (_lights.size() == 0) return;
    _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
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

CanvasComponent* World::GetCanvasComponent()
{
	return m_mainCanvas;
}