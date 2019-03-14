#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>

class RefillStationComponent :public XMLComponent
{
public:
	void Start();
	void Update(float timeStep);
	void OnTrigger(CollisionInfo* collisionInfo);

	RefillStationComponent();
	virtual ~RefillStationComponent();
	void Blink(bool blink);

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;
private:
	sf::Clock m_animationClock;

	bool isBlinking = false;

	float m_inkGainRate = 0;
	AudioSource* m_audioSource;
	float m_timeTillPlay = 1.6f;
	sf::Music * m_initMusic;
};

