#include "ResolutionScreen.h"
#include "mge/core/WorldManager.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"
#include "game\ResolutionUI.h"


ResolutionScreen::ResolutionScreen()
{
}


ResolutionScreen::~ResolutionScreen()
{
}

void ResolutionScreen::Initialize()
{
	GameObject* canvas = Instantiate<GameObject>();
	SetCanvas(canvas->AddComponent<CanvasComponent>());
	ResolutionUI* resoUI = Instantiate<ResolutionUI>();

	Camera* cam = Instantiate<Camera>();
	this->setMainCamera(cam->GetCameraComponent());
}
