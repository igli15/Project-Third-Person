#include "BalloonComponent.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"


BalloonComponent::BalloonComponent()
{
}


BalloonComponent::~BalloonComponent()
{
}

void BalloonComponent::Awake()
{
	m_grid = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetGrid();

}
