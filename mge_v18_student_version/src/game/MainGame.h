#ifndef TESTWROLD_HPP
#define TESTWORLD_HPP

#include "mge/core/AbstractGame.hpp"

class MainGame : public AbstractGame
{
public:
	MainGame();
	virtual ~MainGame();


protected:

	virtual void LoadResources(ResourceManager* resourceManager);
	virtual void CreateWorld() override;
	//virtual void _render() override;

};

#endif
