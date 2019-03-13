#include "BalloonComponent.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"
#include "game/components/PlayerDataComponent.h"
#include "mge/core/GameObject.hpp"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"

BalloonComponent::BalloonComponent()
{
}


BalloonComponent::~BalloonComponent()
{
}

void BalloonComponent::Parse(rapidxml::xml_node<>* compNode)
{

}

void BalloonComponent::Awake()
{
	Component::Awake();
	m_initMusic = AbstractGame::Instance()->GetResourceManager()->GetMusic("");
	m_audioSource = m_gameObject->AddComponent<AudioSource>();
	m_audioSource->SetMusic(m_initMusic);
}

void BalloonComponent::Explode(PlayerDataComponent* playerData)
{
	if (!m_exploded)
	{
		m_audioSource->PlayOneShotSound("balloonExplode");
		GameObject* player1 = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(0);
		GameObject* player2 = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(1);
		
		TileComponent* p1Tile = m_grid->GetTileOnPos(player1->transform->LocalPosition());
		TileComponent* p2Tile = m_grid->GetTileOnPos(player2->transform->LocalPosition());

		PlayerDataComponent* p1Data = player1->GetComponent<PlayerDataComponent>();
		PlayerDataComponent* p2Data = player2->GetComponent<PlayerDataComponent>();

		m_exploded = true;

		auto tiles = m_grid->GetTilesInARange(m_gameObject->transform->LocalPosition(), 7, 7);
		for (int i = 0; i < tiles.size(); i++)
		{
			if (p1Tile != nullptr && tiles[i]->GridPos() == p1Tile->GridPos() && p1Data->MatType() != playerData->MatType())
			{
				p1Data->OnDeath();
			}
			else if (p2Tile != nullptr && tiles[i]->GridPos() == p2Tile->GridPos() && p2Data->MatType() != playerData->MatType())
			{
				p2Data->OnDeath();
			}

			if(tiles[i]->GridPos() != m_tile->GridPos()) tiles[i]->ActivateGridElement(playerData);

			tiles[i]->PaintTile(playerData->MatType());
		}
		m_gameObject->Destroy();
		if(m_tile != nullptr) m_tile->RemoveGridElement(this);
	}
}

void BalloonComponent::OnDestroy()
{
}

void BalloonComponent::OnPainted(PlayerDataComponent* playerData)
{
	GridElement::OnPainted(playerData);

	Explode(playerData);

}
