#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "mge/core/Component.h"

class TestComponent : public Component
{
public:
	TestComponent();
	virtual ~TestComponent();

	void Awake() override;
	void Start() override;
	void Update(float timeStep) override;

protected:

private:
};

#endif // TESTCOMPONENT_H