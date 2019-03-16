#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/components/LightComponent.h"

Light::Light()
{}

Light::~Light() {
}

void Light::Load()
{
	m_lightComponent = AddComponent<LightComponent>();
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
   // if (previousWorld != nullptr) previousWorld->unregisterLight(m_lightComponent);
	if (newWorld != nullptr) newWorld->registerLight(m_lightComponent);

}

LightComponent * Light::GetLightComponent()
{
	return m_lightComponent;
}


