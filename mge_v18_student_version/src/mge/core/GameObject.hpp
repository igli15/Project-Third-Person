#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include "glm.hpp"
#include "Component.h"
#include "../components/Transform.h"
#include "../components/MeshRenderer.h"

class AbstractMaterial;
class World;
class Mesh;
class Transform;
class RigidBody;
class CollisionInfo;
/**
 * A GameObject wraps all data required to display an object, but knows nothing about OpenGL or rendering.
 */
class GameObject
{
	public:
		GameObject();
		virtual ~GameObject();

		Transform* transform = nullptr;

		World* GetWorld();

        void setName (const std::string& pName);
        std::string getName() const;

		void SetRigidBody(RigidBody* rigidBody);
		RigidBody* GetRigidBody();

		void Destroy();
		bool IsMarkedForDestruction();

		void SetMeshRenderer(MeshRenderer* meshRenderer);
		MeshRenderer* GetMeshRenderer() const;

        //mesh and material should be shared as much as possible
		void setMaterial (AbstractMaterial* pMaterial);
		AbstractMaterial* getMaterial() const;

		//Load is used to attach comonents only!!
		virtual void Load();

		virtual void Awake();
		virtual void Start();
		virtual void Update(float pStep);
		virtual void OnCollision(CollisionInfo* collisionInfo);
		virtual void OnTrigger(CollisionInfo* collisionInfo);
		virtual void OnDestroy();

        //child management, note that add/remove and setParent are closely coupled.
        //a.add(b) has the same effect as b.setParent(a)
        //Adding a gameobject or resetting the parent, recursively passes on the world pointer to all child objects

        //shortcut to set the parent of pChild to ourselves
		void add (GameObject* pChild);
		//shortcut to set the parent of pChild to nullptr
		void remove (GameObject* pChild);

		void setParent (GameObject* pGameObject);
		GameObject* getParent() const;

        int getChildCount() const;
        GameObject* getChildAt (int pIndex) const;

		unsigned ID() const; //Get ID

		//Add a Component of the specified type to the GameObject
		template<typename T>
		T* AddComponent()
		{
			if (std::is_base_of<Component, T>())
			{
				T* component = new T();
				m_attachedComponents.push_back(component);
				component->SetGameObject(this);
				return component;
			}
			else
			{
				std::cout << "you can only attach a component" << std::endl;
				return nullptr;
				throw;
			}

		}
		
		//Get a Component attached to this GameObject
		template<typename T>
		T* GetComponent()     //Gets a component from the list of attached components
		{
			for (int i = 0; i < m_attachedComponents.size(); ++i)
			{
				//if (typeid(T) == typeid(*m_attachedComponents[i]))
				if(dynamic_cast<T*>(m_attachedComponents[i]) != NULL)
				{
					return (T*)m_attachedComponents[i];
				}
			}

			std::cout << "could not find an component of that type: "<<typeid(T).name()  << std::endl;
			return nullptr;
		}

	protected:
		std::string _name;

        GameObject* _parent = nullptr;
		std::vector<GameObject*> _children;

		MeshRenderer* m_meshRenderer = nullptr;

		RigidBody* _rigidBody;
		AbstractMaterial* _material;
		World* _world;

        //update children list administration
        void _innerAdd (GameObject* pChild);
		void _innerRemove (GameObject* pChild);

		//used to pass on pointer to the world to a gameobject
		virtual void _setWorldRecursively (World* pWorld);

    private:
        GameObject (const GameObject&);
		GameObject& operator= (const GameObject&);
		bool operator == (const GameObject & other);

		std::vector<Component*> m_attachedComponents;

		bool m_markedForDestruction = false;

		static unsigned m_idCounter; 

		unsigned m_id;
};

#endif // GAMEOBJECT_HPP
