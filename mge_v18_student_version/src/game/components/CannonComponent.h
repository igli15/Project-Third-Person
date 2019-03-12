#pragma once

#include "GridElement.h"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/GameObject.hpp"
class PlayerDataComponent;

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};


class CannonComponent : public GridElement
{

public:
	CannonComponent();
	virtual ~CannonComponent();

	virtual void OnPainted(PlayerDataComponent* playerData) override;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void Start() override;


private:
	int m_shootingRange = 6;

	Direction m_facingDir;
	int m_dirInt;
	
	void ShootInFacingDir(PlayerDataComponent* playerData);

	bool shot = false;

	AudioSource* m_audioSource;
	float m_timeTillPlay = 1.6f;
	sf::Music * m_initMusic;
};

