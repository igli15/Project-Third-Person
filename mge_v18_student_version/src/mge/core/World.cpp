#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"

World::World()
{
	_world = this;
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera () {
    return _mainCamera;
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

void World::DestroyObject(GameObject * object)
{
	if (object != this)
	{
		remove(object);
		delete object;
	}
}
