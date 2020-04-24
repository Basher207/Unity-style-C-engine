#pragma once

#include <unordered_set>
#include <map>
#include <vector>
#include <typeinfo>
#include <string.h>
#include "Transform.hpp"
#include "MonoBehaviour.hpp"

//Renderer abstract base class to be used by all renderers
class Renderer : public MonoBehaviour {
public:
	void Awake ();
	virtual void Render() = 0;
};

//Mono container stores a pointer to a MonoBehavior, and info about it's size
//This is used to make copies of a gameObject
class MonoContainer {
public:
	MonoBehaviour* mono;
	size_t mono_size;
	MonoContainer (MonoBehaviour* mono, size_t mono_size);
};
//GameObject, base of everything in the game. It manages MonoBehavior scripts
class GameObject {
	static std::unordered_set<MonoBehaviour*> startFunctions; //A list of MonoBehaviors that needs Start to be called on
	static std::unordered_set<MonoBehaviour*> updateFunctions;//A list of Update functions that Update needs to be called on
	static std::unordered_set<GameObject*> destroyList;		  //A destroy list, destroy is called on objects on the beginning of the next frame 
	
	~GameObject();//Private destructor, to force use of the Destroy function
public:
	static void UpdateFrame (); //Updates all MonoBehaviors

	Transform transform;//Transform that belongs to the gameObject
	std::vector<MonoContainer> components;  // Components, of the gameobject
	std::unordered_set<Renderer*> renderers;// Renderers that this gameObject contains, these are used to Render by the Transform render Recursion.

	GameObject (); //Create a new GameObject
	GameObject* GetCopy (); //Gets an exact copy of this gameObject, and returns a pointer to it (Note this even copies all the associated components)
	void Destroy(); //Sets this gameobject to be destroyed at the start of the next frame

	//A template to Get a component out of the gameObject
	//It is necciesry to have the implemenation in the header
	//As unique types are compiled that the GameObject.cpp script is not aware of
	template<class T1>
	T1* GetComponent () {
		for (MonoContainer monoCont : this->components) { //Loops through the components
			T1* cast = dynamic_cast<T1*>(monoCont.mono);
			if (cast) //If castable to requested type return the instance
				return cast;
		}
		return 0;// Other wise return null
	}

	//Adds a MonoBehavior component to a gameObject
	//The use a of a static cast to a MonoBehavior raises a compile error
	//if a non MonoBehavior type is attempted to be passed
	template<class T2>
	T2* AddComponent() {
		T2* newComponent = new T2();//Creates a new instance of the generic type
		MonoBehaviour* mono = static_cast<MonoBehaviour*>(newComponent); //Casts the script to a monobehavior


		this->components.push_back(MonoContainer(mono, sizeof(T2)));//Adds the MonoBehavior in a container 

		mono->gameObject = this; 			//Sets the gameObject reference of the monoBehavior script to this gameObject
		mono->transform  =&this->transform; //Sets the transform  reference of the monoBehavior script to this gameObject
		
		mono->Awake(); //Calls Awake in the same stack frame as the AddComponent
		GameObject::startFunctions.insert(mono); //Sets the mono object start to be called at the start of the next frame

		return newComponent; //Returns a reference to the new instance.
	}
};