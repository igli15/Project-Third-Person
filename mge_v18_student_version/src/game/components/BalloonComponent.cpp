#include "BalloonComponent.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"


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
		auto tiles = m_grid->GetTilesInARange(m_gameObject->transform->LocalPosition(), 6, 6);
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i]->PaintTile(type);
		}
		m_gameObject->Destroy();
		m_exploded = true;
	}
}

void BalloonComponent::OnPainted(TileType type)
{
	GridElement::OnPainted(type);

	Explode(type);

}
