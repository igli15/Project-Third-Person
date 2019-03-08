#include "BalloonComponent.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"
#include "game/components/PlayerDataComponent.h"
#include "mge/core/GameObject.hpp"

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
}

void BalloonComponent::Explode(TileType type)
{
	if (!m_exploded)
	{
		GameObject* player1 = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(0);
		GameObject* player2 = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(1);
		
		TileComponent* p1Tile = m_grid->GetTileOnPos(player1->transform->LocalPosition());
		TileComponent* p2Tile = m_grid->GetTileOnPos(player2->transform->LocalPosition());

		PlayerDataComponent* p1Data = player1->GetComponent<PlayerDataComponent>();
		PlayerDataComponent* p2Data = player2->GetComponent<PlayerDataComponent>();

		auto tiles = m_grid->GetTilesInARange(m_gameObject->transform->LocalPosition(), 6, 6);
		for (int i = 0; i < tiles.size(); i++)
		{
			if (p1Tile != nullptr && tiles[i]->GridPos() == p1Tile->GridPos() && p1Data->MatType() != type)
			{
				p1Data->OnDeath();
			}
			else if (p2Tile != nullptr && tiles[i]->GridPos() == p2Tile->GridPos() && p2Data->MatType() != type)
			{
				p2Data->OnDeath();
			}

			tiles[i]->PaintTile(type);
		}
		m_gameObject->Destroy();
		m_exploded = true;
	}
}

void BalloonComponent::OnDestroy()
{
	m_tile->RemoveGridElement(this);
}

void BalloonComponent::OnPainted(TileType type)
{
	GridElement::OnPainted(type);

	Explode(type);

}
