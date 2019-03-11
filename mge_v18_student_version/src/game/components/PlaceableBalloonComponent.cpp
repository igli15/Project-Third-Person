#include "PlaceableBalloonComponent.h"
#include "PlayerDataComponent.h"

PlaceableBalloonComponent::PlaceableBalloonComponent()
{
}


PlaceableBalloonComponent::~PlaceableBalloonComponent()
{
}

void PlaceableBalloonComponent::Parse(rapidxml::xml_node<>* compNode)
{

}

void PlaceableBalloonComponent::OnPainted(PlayerDataComponent * playerData)
{
	GridElement::OnPainted(playerData);
	Explode(playerData->MatType());
}


