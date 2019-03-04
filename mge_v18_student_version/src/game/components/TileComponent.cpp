#include "TileComponent.h"

#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/AbstractGame.hpp"

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
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceMat"));
		m_tileType = TileType::ICE;
	}
	else if (type == TileType::LAVA)
	{
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaMat"));
		m_tileType = TileType::LAVA;
	}
}

