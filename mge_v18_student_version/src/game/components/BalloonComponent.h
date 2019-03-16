#pragma once
#include "game/components/GridElement.h"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/GameObject.hpp"


class BalloonComponent : public GridElement
{

public:
	BalloonComponent();
	virtual ~BalloonComponent();

	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void Awake();
	
	void Explode(PlayerDataComponent* playerData);

	void OnDestroy() override;

	virtual void OnPainted(PlayerDataComponent* playerData) override;

protected:
	bool m_exploded = false;
	AudioSource* m_audioSource;
	float m_timeTillPlay = 1.6f;
	sf::Music * m_initMusic;


};

