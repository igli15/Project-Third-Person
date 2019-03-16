#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

class LightComponent;

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light();
		virtual ~Light();

		void Load() override;

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;

		LightComponent* GetLightComponent();

private:
	LightComponent* m_lightComponent;
};

#endif // LIGHT_HPP
