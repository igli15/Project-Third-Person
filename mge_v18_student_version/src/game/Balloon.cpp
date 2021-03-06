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
	if (m_scaleTween != nullptr)
	{
		Tweener::DeleteTween(m_scaleTween);
		m_scaleTween = nullptr;
	}
}

void Balloon::Load()
{
	GameObject::Load();

	AddComponent<MeshRenderer>()->SetMesh(AbstractGame::Instance()->GetResourceManager()->GetMesh("balloon"));

	setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("balloonMat"));


	m_balloonComponent = AddComponent<BalloonComponent>();

}

void Balloon::Update(float timeStep)
{
	GameObject::Update(timeStep);
	
	if (m_scaleTween != nullptr)
		m_scaleTween->onStep([this](float x, float y, float z) {if(transform != nullptr) transform->SetScale(glm::vec3(x, y, z)); return false; });

}

void Balloon::OnDestroy()
{
	GameObject::OnDestroy();

}

void Balloon::ScaleUp()
{
	std::cout << "BALLOON TWEEN: "<<ID() << std::endl;
	transform->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	m_scaleTween = Tweener::GenerateTween<float>(0, 1, 0, 1, 0, 1, 1500, 1500, 1500);
	*m_scaleTween = m_scaleTween->via(tweeny::easing::bounceOut);

}

BalloonComponent * Balloon::GetBalloonComponent()
{
	return m_balloonComponent;
}
