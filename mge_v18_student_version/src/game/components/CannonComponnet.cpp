#include "CannonComponnet.h"
#include "GridComponent.h"
#include "mge/core/GameObject.hpp"
#include "PlayerDataComponent.h"

CannonComponnet::CannonComponnet()
{

}


CannonComponnet::~CannonComponnet()
{
}

void CannonComponnet::OnPainted(PlayerDataComponent* playerData)
{
	auto tiles = m_grid->GetNeighbourTiles(m_gameObject->transform->LocalPosition(), playerData->GetEnemy()->transform->LocalPosition(),
											4,false,false, []() {});
}

void CannonComponnet::Parse(rapidxml::xml_node<>* compNode)
{

}
