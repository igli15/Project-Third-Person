#include "GridComponent.h"
#include "game/components/TileComponent.h"
#include <iostream>

GridComponent::GridComponent()
{
}


GridComponent::~GridComponent()
{
}

void GridComponent::Awake()
{
	
}

void GridComponent::SetWidth(int width)
{
	m_width = width;
}

void GridComponent::SetHeight(int height)
{
	m_height = height;
}

void GridComponent::SetTileRadius(int r)
{
	m_tileRadius = r;
}

int GridComponent::Width() const
{
	return m_width;
}

int GridComponent::Height() const
{
	return m_height;
}

int GridComponent::TileRadius() const
{
	return m_tileRadius;
}

void GridComponent::AddTile(TileComponent * tile)
{
	for (size_t i = 0; i < m_height; i++)
	{
		if (m_tileGrid.at(i).size() < m_width)
		{
			m_tileGrid.at(i).push_back(tile);
			return;
		}
	}
}

void GridComponent::Parse(rapidxml::xml_node<>* compNode)
{
	std::cout << "Parsing Grid Component...." << std::endl;
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::cout << a->name() << " : " << a->value() << std::endl;
		std::string attributeName = a->name();
		if (attributeName == "gridSizeX")
		{
			SetWidth(atoi(a->value()));
		}
		else if (attributeName == "gridSizeY")
		{
			SetHeight(atoi(a->value()));
		}
		else if (attributeName == "tileRadius")
		{
			SetTileRadius(atoi(a->value()));
		}
	}

	m_tileGrid.resize(m_height, std::vector<TileComponent*>());
}

TileComponent * GridComponent::GetTileAt(int x, int y)
{
	return m_tileGrid[y][x];
}
