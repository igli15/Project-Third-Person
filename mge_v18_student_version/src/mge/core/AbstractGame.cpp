#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/WorldManager.h"
#include "mge/core//CollisionManager.h"
#include "game/MainWorld.h"
#include "ResourceManager.h"
#include "mge/core/EventQueue.h"
#include "game/MenuScene.h"
#include "mge/core/Tweener.h"
#include "mge/config.hpp"

AbstractGame* AbstractGame::m_instance = nullptr;

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL), _fps(0)
{
	m_instance = this;

	std::cout << "Creating Resource Manager" << std::endl;
	m_resourceManager = new ResourceManager();
	std::cout << "Resource Manager is Created" << std::endl;

	std::cout << "Creating Collision Manager" << std::endl;
	m_collisionManager = new CollisionManager();
	std::cout << "Resource Collision is Created" << std::endl;

	std::cout << "Creating Event Queue" << std::endl;
	m_eventQueue = new EventQueue();
	std::cout << "EventQueue Created" << std::endl;

}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::Initialize() {
    std::cout << "Initializing engine..." << std::endl << std::endl;

    _initializeWindow();

	sf::Texture* metroLogoTex = m_resourceManager->LoadSFMLTexture(config::MGE_TEXTURE_PATH + "Engine/BackgroundOverlay.png", "metroLogos");
	sf::Texture* logoTex = m_resourceManager->LoadSFMLTexture(config::MGE_TEXTURE_PATH + "Engine/mgeLogoInTheMiddle.png", "logo");
	sf::Texture* backgrosliderundTex = m_resourceManager->LoadSFMLTexture(config::MGE_TEXTURE_PATH + "Engine/white_line.png", "slider");

	sf::Sprite* metroLogo = new sf::Sprite();
	metroLogo->setTexture(*metroLogoTex);

	sf::Sprite* logo = new sf::Sprite();
	logo->setTexture(*logoTex);

	sf::Sprite* slider = new sf::Sprite();
	slider->setTexture(*backgrosliderundTex);
	
	_window->clear();
	_window->draw(*logo);
	_window->draw(*metroLogo);
	slider->setPosition(755, 575);
	slider->setScale(0, 1);
	auto t  = Tweener::GenerateTween<float>(0, 1, 15000);
	*t = t->via(tweeny::easing::quadraticOut);
	while (t->progress() < 1)
	{
		_window->clear();
		_window->draw(*logo);
		_window->draw(*metroLogo);
		slider->setScale(t->step(16),1);
		_window->draw(*slider);
		_window->display();
	}
	_window->display();

    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
	
    std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

void AbstractGame::LoadResources(ResourceManager * resourceManager)
{
	
}

///SETUP

void AbstractGame::_initializeWindow() 
{
	float m_windowWidth = 1920;
	float m_windowHeight = 1080;

	std::cout << "Initializing window with Width: "<<m_windowWidth<<" and Height: "<<m_windowHeight << std::endl;

	_window = new sf::RenderWindow( sf::VideoMode(m_windowWidth,m_windowHeight), "MGE", sf::Style::Default, sf::ContextSettings(24,8,8,3,3));
	//_window->setVerticalSyncEnabled(true);
    std::cout << "Window initialized." << std::endl << std::endl;
}

void AbstractGame::_printVersionInfo() {
	std::cout << "Context info:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    //print some debug stats for whoever cares
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::_initializeGlew() {
	std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	std::cout << "Initializing renderer..." << std::endl;
	_renderer = new Renderer();
    _renderer->setClearColor(0,0,0);
    std::cout << "Renderer done." << std::endl << std::endl;
}

void AbstractGame::_initializeWorld() {
    //setup the world
	std::cout << "Initializing world..." << std::endl;
	//_world = new World();
	_world = m_worldManager->CreateWorld<MenuScene>("MenuScene");
    std::cout << "World initialized." << std::endl << std::endl;
}

void AbstractGame::InitializeWorldManager()
{
	std::cout << "Creating World Manager" << std::endl;
	m_worldManager = new WorldManager();
	std::cout << "World Manager is Created" << std::endl;
}

void AbstractGame::CreateWorld()
{
	InitializeWorldManager();
	_initializeWorld();
}

///MAIN GAME LOOP

void AbstractGame::run()
{
    //setting to calculate fps
	sf::Clock renderClock;
    int frameCount = 0;
    float timeSinceLastFPSCalculation = 0;
	
	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen()) {
		//std::cout << "FPS: " << _fps << std::endl;
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{

            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			_window->clear(sf::Color(47,64,51,255));



			m_worldManager->ClearOldWorld();

			m_worldManager->GetCurrentWorld()->ClearMarkedGameObject();

			m_eventQueue->HandleEvents();

		    while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                _update(timePerFrame.asSeconds());

				Tweener::UpdateAllTweens((int)m_tweenDeltaTime);
		    }

			_render();
			
			if(m_worldManager->GetCurrentWorld()->GetCanvasComponent() != nullptr)
			{
				m_worldManager->GetCurrentWorld()->GetCanvasComponent()->DrawAllUISprites(_window);
				m_worldManager->GetCurrentWorld()->GetCanvasComponent()->DrawAllTexts(_window);
			}
			


			_window->display();

            //fps count is updated once every 1 second
            frameCount++;
            timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
            if (timeSinceLastFPSCalculation > 1) {
                _fps = frameCount/timeSinceLastFPSCalculation;
                timeSinceLastFPSCalculation -= 1;
				std::cout << _fps << std::endl;
                frameCount = 0;
            }


		}

		m_tweenDeltaTime = timeSinceLastUpdate.asMilliseconds();
		//empty the event queue
		_processEvents();
    }
}

AbstractGame * AbstractGame::Instance()
{
	return m_instance;
}

WorldManager * AbstractGame::GetWorldManager()
{
	return m_worldManager;
}

sf::RenderWindow * AbstractGame::GetWindow()
{
	return _window;
}

ResourceManager * AbstractGame::GetResourceManager()
{
	return m_resourceManager;
}

CollisionManager * AbstractGame::GetCollisionManager()
{
	return m_collisionManager;
}

EventQueue * AbstractGame::GetEventQueue()
{
	return m_eventQueue;
}

unsigned AbstractGame::WindowWidth() const
{
	return m_windowWidth;
}

unsigned AbstractGame::WindowHeight() const
{
	return m_windowHeight;
}

void AbstractGame::_update(float pStep) {
    m_worldManager->GetCurrentWorld()->Update(pStep);
}

void AbstractGame::_render () {
    _renderer->render(m_worldManager->GetCurrentWorld());
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you for example you could implement a
        //SystemEventDispatcher / SystemEventListener pair which allows Listeners to
        //register with the dispatcher and then do something like:
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
	}
}



