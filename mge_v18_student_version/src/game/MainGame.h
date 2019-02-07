#ifndef TESTWROLD_HPP
#define TESTWORLD_HPP

#include "mge/core/AbstractGame.hpp"

class MainGame : public AbstractGame
{
public:
	MainGame();
	virtual ~MainGame();

	virtual void initialize() override;

protected:

	virtual void Initialize() override;
	//virtual void _render() override;

};

#endif
