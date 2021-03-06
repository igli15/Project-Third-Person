#include "TileComponent.h"

#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/AbstractGame.hpp"
#include "game/components/GridComponent.h"
#include "game/components/GridElement.h"
#include "PlayerDataComponent.h"

TileComponent::TileComponent()
{
}


TileComponent::~TileComponent()
{
}

void TileComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "TileType")
		{
			std::string value(a->value());
			if (value == "DEFAULT")
			{
				m_tileType = TileType::DEFAULT;
			}
			else if (value == "ICE")
			{
				PaintTile(TileType::ICE);
			}
			else if (value == "LAVA")
			{
				PaintTile(TileType::LAVA);
			}
		}
		if (attributeName == "isPaintable")
		{
			std::string value(a->value());
			m_isPaintable = (value == "True");
		}
	}
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

bool TileComponent::IsPaintable()
{
	return m_isPaintable;
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
	if (!m_isPaintable) return;

	
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

		oldMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceMat"));
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
		oldMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaMat"));
		m_tileType = TileType::LAVA;
	}
}

void TileComponent::SetGrid(GridComponent * grid)
{
	m_grid = grid;
}

void TileComponent::SetGridElement(GridElement * gridElement)
{
	if (gridElement != nullptr)
	{
		RemoveGridElement(gridElement);
	}

	m_gridElement = gridElement;
	gridElement->SetTile(this);
}

void TileComponent::RemoveGridElement(GridElement * gridElement)
{
	if(m_gridElement != nullptr) m_gridElement = nullptr;
	gridElement->SetTile(nullptr);
}

void TileComponent::ActivateGridElement(PlayerDataComponent* playerData)
{
	if (m_gridElement != nullptr)
	{
		m_gridElement->OnPainted(playerData);
	}
}

bool TileComponent::IsFree()
{
	return (m_gridElement == nullptr);
}

void TileComponent::SelectTile(PlayerDataComponent* playerData)
{
	if(m_gameObject->getMaterial()==  AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaSelection") ||
		m_gameObject->getMaterial() == AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceSelection") )return;

	oldMat = dynamic_cast<TextureMaterial*>(m_gameObject->getMaterial());
	if (playerData->GetPlayerNumber() == 1)
	{
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaSelection"));
	}
	else
	{
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceSelection"));
	}
}

void TileComponent::DeSelectTile()
{
	if(oldMat != nullptr && (oldMat != AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaSelection") || oldMat != AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceSelection")) )
	m_gameObject->setMaterial(oldMat);
}

