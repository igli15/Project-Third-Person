#include "TileComponent.h"

#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/AbstractGame.hpp"
#include "game/components/GridComponent.h"

TileComponent::TileComponent()
{
}


TileComponent::~TileComponent()
{
}

void TileComponent::Parse(rapidxml::xml_node<>* compNode)
{
}

void TileComponent::SetGridPos(glm::ivec2 gridPos)
{
	m_gridPos = gridPos;
}

glm::ivec2 TileComponent::GridPos()
{
	return m_gridPos;
}

bool TileComponent::IsPainted()
{
	return m_isPainted;
}

void TileComponent::SetTileType(TileType newType)
{
	m_tileType = newType;
}

TileType TileComponent::GetTileType()
{
	return m_tileType;
}

void TileComponent::PaintTile(TileType type)
{
	m_isPainted = true;

	if (type == TileType::ICE)
	{
		if (m_tileType == ICE) return;

		if (m_tileType == TileType::LAVA)
		{
			m_grid->DecreaseTileCount(TileType::LAVA);
		}

		m_grid->IncreaseTileCount(TileType::ICE);

		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceMat"));
		m_tileType = TileType::ICE;
		
	}
	else if (type == TileType::LAVA)
	{
		if (m_tileType == LAVA) return;

		if (m_tileType == TileType::ICE)
		{
			m_grid->DecreaseTileCount(TileType::ICE);
		}

		m_grid->IncreaseTileCount(TileType::LAVA);

		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaMat"));
		m_tileType = TileType::LAVA;
	}
}

void TileComponent::SetGrid(GridComponent * grid)
{
	m_grid = grid;
}

