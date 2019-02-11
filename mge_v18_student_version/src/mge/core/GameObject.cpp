#include <iostream>
#include "GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

GameObject::GameObject()
:	_name( "" ), _parent(nullptr), _children(),
    _material(nullptr), _world(nullptr)

{
	transform = AddComponent<Transform>();
}

GameObject::~GameObject()
{
    //detach all children
    std::cout << "GC running on:" << _name << std::endl;

    while (_children.size() > 0) {
        GameObject* child = _children[0];
        remove (child);
        delete child;
    }

	//erase all attached components;
	for (unsigned int i = m_attachedComponents.size(); i > 0;) {
		--i;
		delete m_attachedComponents[i];
		m_attachedComponents.pop_back();
	}

	std::cout <<"Components Left "<< m_attachedComponents.size()<<std::endl;

    //do not forget to delete behaviour, material, mesh, collider manually if required!
}


World * GameObject::GetWorld()
{
	return _world;
}

void GameObject::setName (const std::string& pName)
{
    _name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}


void GameObject::setMaterial(AbstractMaterial* pMaterial)
{
	if (!pMaterial->IsRegistered())
	{
		std::cout << "Material has to be registered by the ResourceManager in order to be used" << std::endl;
		throw;
	}
    _material = pMaterial;
}

AbstractMaterial * GameObject::getMaterial() const
{
    return _material;
}

void GameObject::Destroy()
{
	m_markedForDestruction = true;
	OnDestroy();
}

bool GameObject::IsMarkedForDestruction()
{
	return m_markedForDestruction;
}

void GameObject::SetMeshRenderer(MeshRenderer * meshRenderer)
{
	m_meshRenderer = meshRenderer;
}

MeshRenderer * GameObject::GetMeshRenderer() const
{
	return m_meshRenderer;
}

void GameObject::Load()
{
	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->Load();
	}
}

void GameObject::Awake()
{
	for (int i = 0; i < m_attachedComponents.size(); ++i) {

		m_attachedComponents[i]->Awake();
	}

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->Awake();
	}
}

void GameObject::Start()
{
	for (int i = 0; i < m_attachedComponents.size(); ++i) {

		m_attachedComponents[i]->Start();
	}
	
	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->Start();
	}
}

void GameObject::setParent (GameObject* pParent) {
    //remove from previous parent
    if (_parent != nullptr) {
        _parent->_innerRemove(this);
    }

    //set new parent
    if (pParent != nullptr) {
        pParent->_innerAdd(this);
    }

    //if we have been detached from our parent, make sure
    //the world reference for us and all our children is set to null
    //if we have been attached to a parent, make sure
    //the world reference for us and all our children is set to our parent world reference
    //(this could still be null if the parent or parent's parent is not attached to the world)
    if (_parent == nullptr) {
        _setWorldRecursively(nullptr);
    } else {
        //might still not be available if our parent is not part of the world
        _setWorldRecursively(_parent->_world);
    }
}

void GameObject::_innerRemove (GameObject* pChild) {
    for (auto i = _children.begin(); i != _children.end(); ++i) {
        if (*i == pChild) {
            _children.erase(i);
            pChild->_parent = nullptr;
            return;
        }
    }
}

void GameObject::_innerAdd(GameObject* pChild)
{
	_children.push_back(pChild);
   pChild->_parent = this;
}

void GameObject::add (GameObject* pChild) {
    pChild->setParent(this);
}

void GameObject::remove (GameObject* pChild) {
    pChild->setParent(nullptr);
}

GameObject* GameObject::getParent() const {
    return _parent;
}



void GameObject::Update(float pStep)
{

	for (int i = 0; i < m_attachedComponents.size(); ++i) {

		m_attachedComponents[i]->Update(pStep);
	}

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->Update(pStep);
	}
}

void GameObject::OnDestroy()
{
	for (int i = 0; i < m_attachedComponents.size(); ++i) {

		m_attachedComponents[i]->OnDestroy();
	}

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->OnDestroy();
	}
}

void GameObject::_setWorldRecursively (World* pWorld) {
    _world = pWorld;

    for (int i = _children.size()-1; i >= 0; --i ) {
        _children[i]->_setWorldRecursively (pWorld);
    }
}

int GameObject::getChildCount() const {
    return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) const {
    return _children[pIndex];
}

