#pragma once
#include <unordered_set>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <MonoBehaviour.hpp>


class Transform : public MonoBehaviour {
	Transform* parent = 0;//Parent, 0 if null
	void SetChild(Transform* child); //Adds a Transform as a child
	void RemoveChild(Transform* child); //Removes a child from the children list
public:
	//Note the usage of set here is to make it easier to remove and get indexes using an object reference
	//as oppose to working with indexes.
	static std::unordered_set<Transform*> masterParents; //Parents without children, all of them will be rendered (if they have a renderer attached)
	static void RenderMasterParents ();	//Recursively renders all the Transforms from parents to children
	std::unordered_set<Transform*> children;//A list of pointers to all the children

	glm::vec3 localPos {0.0f, 0.0f, 0.0f};				//The current Matrix is offseted, rotated, and scaled by these values 
	glm::quat localRotation {0.0f, 0.0f, 0.0f, 0.0f};	//and is only popped after all the children Render
	glm::vec3 localScale {1.0f, 1.0f, 1.0f};			//Hence why it's local, because it's dependednt on the parents

	void Awake();

	void SetParent(Transform* parent); //Sets parent
	void PushTransformMatrix(); //Pushes the Matrix of this transform
	
	void Render();
	void CopyValues(Transform* transform);
	
	glm::vec3 GetForward();
	glm::vec3 GetUp();
	glm::vec3 GetRight();
	void LookAt(glm::vec3 pos, glm::vec3 up = glm::vec3(0.f,1.f,0.f));

	// glm::vec3 GetUp();
	// void SetUp(glm::vec3 forward);

	void OnDestroy ();							   //children lists and passed around in general.
};