#ifndef TESTWROLD_HPP
#define TESTWORLD_HPP

#include "mge/core/AbstractGame.hpp"

class TestWorld : public AbstractGame
{
public:
	TestWorld();
	virtual ~TestWorld();

	virtual void initialize() override;

protected:

	virtual void _initializeScene() override;
	//virtual void _render() override;

};

#endif
