#pragma once

class GameObject;
class Transform;

class MonoBehaviour {
public:
	Transform* transform;	//Transform that's on the gameObject the script is on
	GameObject* gameObject; //GameObject that this script is on


	virtual void Awake(); //Called in the same stack frame when a script is added
	virtual void Start(); //Called at the start of the next frame

	virtual void Update();
	virtual void OnDestroy(); //Called when the gameobject is destroyed, sorta like the destroctor
							  //This is useful so OnDestroy can be called on all the objects before
							  //The memory is freed on all gameObject components
};