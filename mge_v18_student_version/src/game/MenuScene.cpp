#include "MenuScene.h"
#include "MenuUI.h"
#include "mge/core/WorldManager.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"


MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}


void MenuScene::Initialize()
{
	GameObject* canvas = Instantiate<GameObject>();
	SetCanvas(canvas->AddComponent<CanvasComponent>());
	MenuUI* menuUI = Instantiate<MenuUI>();

	Camera* cam = Instantiate<Camera>();
	this->setMainCamera(cam->GetCameraComponent());

}
