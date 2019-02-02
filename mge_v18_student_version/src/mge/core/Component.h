#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Awake();
	virtual void Start();
	virtual void Update(float timeSteps);

	GameObject* GetGameObject();
	void SetGameObject(GameObject* obj);

protected:

	GameObject* m_gameObject = nullptr;

};

#endif // COMPONENT_H