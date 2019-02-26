#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class CollisionInfo;

class Component
{
public:
	Component();
	virtual ~Component();

	//Awake is called just before start is called.
	virtual void Awake();

	//Start is called once in the beggining  
	virtual void Start();

	//Update loop
	virtual void Update(float timeSteps);

	//OnCollision is called each frame when gameObject is colliding
	virtual void OnCollision(CollisionInfo* collisionInfo);

	virtual void OnDestroy();

	//Get the parent Gameobject of the Component
	GameObject* GetGameObject();

	//Set the parent GameObject of the Component
	//Not advised to be used outside of the engine!
	void SetGameObject(GameObject* obj);

protected:

	GameObject* m_gameObject = nullptr;

};

#endif // COMPONENT_H