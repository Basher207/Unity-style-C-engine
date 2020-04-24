#include <GameObject.hpp>
#include <typeinfo>
#include <stdio.h>

void Renderer::Awake () {
	this->gameObject->renderers.insert(this);
}

MonoContainer::MonoContainer (MonoBehaviour* mono, size_t mono_size) : mono(mono), mono_size(mono_size) {}

std::unordered_set<MonoBehaviour*> GameObject::startFunctions;
std::unordered_set<MonoBehaviour*> GameObject::updateFunctions;

std::unordered_set<GameObject*> GameObject::destroyList;


GameObject* GameObject::GetCopy () {
	GameObject* copy = new GameObject(); //Creates a new gameobject
	copy->transform.CopyValues(&this->transform); //Copies the value of the transform
	for (MonoContainer monoCont : this->components) {
		MonoBehaviour* mono_cp = (MonoBehaviour*)malloc(monoCont.mono_size);
		memcpy(mono_cp, monoCont.mono, monoCont.mono_size); 
		//Makes an exact copy of the monoBheavior

		mono_cp->transform = &copy->transform;
		mono_cp->gameObject = copy;//Sets there transform and gameObject to thew new object

		mono_cp->Awake(); //Calls Awake to reallocate any memory that the script reallocats

		copy->components.push_back(MonoContainer(mono_cp, monoCont.mono_size)); //pushes the new gameobject into the components of the new object
		GameObject::startFunctions.insert(mono_cp);								//Adds it to the startFunctions list
	}
	return copy;
}

void GameObject::UpdateFrame() {
	for (GameObject* go : GameObject::destroyList) {
		delete go; //First the gameobjects in the destroy list are deleted and cleared
	}
	GameObject::destroyList.clear();

	for(MonoBehaviour* mono : GameObject::startFunctions) {
		mono->Start();
		GameObject::updateFunctions.insert(mono);
		//Than Starts are called and added to the update loop than cleared out of the list
	}
	GameObject::startFunctions.clear();

	for(MonoBehaviour* mono : GameObject::updateFunctions) {
		mono->Update(); //Than the update loop is run
	}
}
void GameObject::Destroy () {
	destroyList.insert(this);
}
GameObject::GameObject () {
	this->transform.transform = &this->transform;
	this->transform.gameObject = this;
	this->transform.Awake();
}
GameObject::~GameObject() {
	//First loop calls all the OnDestroies
	for (MonoContainer monoCont : this->components) {
		startFunctions.erase(monoCont.mono);	
		updateFunctions.erase(monoCont.mono); //Script is taken out of the loops
		monoCont.mono->OnDestroy();	//OnDestroy is called
	}
	transform.OnDestroy();
	//Second loop frees all the memory
	for (MonoContainer monoCont : this->components) 
		delete monoCont.mono;
}