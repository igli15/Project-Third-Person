#include "GridElement.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"


GridElement::GridElement()
{
}


GridElement::~GridElement()
{
}

void GridElement::Awake()
{


}

void GridElement::OnPainted(TileType type)
{
	m_grid = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetGrid();
}

void GridElement::Parse(rapidxml::xml_node<>* compNode)
{
}

void GridElement::SetTile(TileComponent * tile)
{
	m_tile = tile;
}
