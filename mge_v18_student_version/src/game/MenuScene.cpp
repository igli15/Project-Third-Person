#include "MenuScene.h"
#include "MenuUI.h"
#include "mge/core/WorldManager.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/PlayerPrefs.h"

MenuScene::MenuScene()
{

}


MenuScene::~MenuScene()
{
}


void MenuScene::Initialize()
{
	//std::cout << std::endl << "				SETING LEVEL_INDEX" << std::endl;
	//PlayerPrefs::SetInt("LevelIndex", 1);

	GameObject* canvas = Instantiate<GameObject>();
	SetCanvas(canvas->AddComponent<CanvasComponent>());
	MenuUI* menuUI = Instantiate<MenuUI>();

	Camera* cam = Instantiate<Camera>();
	this->setMainCamera(cam->GetCameraComponent());

}
