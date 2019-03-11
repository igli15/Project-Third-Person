#include "Balloon.h"
#include "mge/components/MeshRenderer.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "game/components/BalloonComponent.h"

Balloon::Balloon()
{
}


Balloon::~Balloon()
{
}

void Balloon::Load()
{
	GameObject::Load();

	AddComponent<MeshRenderer>()->SetMesh(AbstractGame::Instance()->GetResourceManager()->GetMesh("balloon"));
	setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("balloonMat"));


	m_balloonComponent = AddComponent<BalloonComponent>();

}

BalloonComponent * Balloon::GetBalloonComponent()
{
	return m_balloonComponent;
}
