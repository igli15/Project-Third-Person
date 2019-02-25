#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/WorldManager.h"
#include "mge/core//CollisionManager.h"
#include "game/MainWorld.h"
#include "ResourceManager.h"
#include "mge/core/EventQueue.h"

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

	_window = new sf::RenderWindow( sf::VideoMode(m_windowWidth,m_windowHeight), "My Game!", sf::Style::Default, sf::ContextSettings(24,8,8,3,3));
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
	_world = m_worldManager->CreateWorld<MainWorld>("MainWorld");
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
			_window->clear();

			if (m_worldManager->GetCurrentWorld()->IsMarkedForDestruction())
			{
				m_worldManager->GetCurrentWorld()->InnerDestroy(m_worldManager->GetCurrentWorld());
			}

			m_worldManager->GetCurrentWorld()->ClearMarkedGameObject();

			m_eventQueue->HandleEvents();

		    while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                _update(timePerFrame.asSeconds());
		    }

			_render();
			
			if(m_worldManager->GetCurrentWorld()->GetCanvasComponent() != nullptr)
			{
				m_worldManager->GetCurrentWorld()->GetCanvasComponent()->DrawAllUISprites(_window);
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



