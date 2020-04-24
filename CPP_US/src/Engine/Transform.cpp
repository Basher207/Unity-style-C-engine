#include <set>
#include <glad.h>
#include <stdio.h>
#include <cstdio>
#include <glm/vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.hpp"
#include "GameObject.hpp"
#include "Math.hpp"

std::unordered_set<Transform*> Transform::masterParents;//Allocates memory to the masterParents set
void Transform::RenderMasterParents () {
	//Master parents are Transforms without parents to call there Renders
    //So they are rendered, and they will render there children.
    for(Transform* masterParent : Transform::masterParents) {
    	masterParent->Render();
    }
}
void Transform::SetChild(Transform* child) {
	if (child != 0)
		this->children.insert(child);
}
void Transform::RemoveChild(Transform* child) {
	this->children.erase(child);
}
void Transform::Awake () {
	Transform::masterParents.erase(this);
	this->SetParent(0);
	this->children.clear();
	Transform::masterParents.insert(this);
}//When constructed, by default the Transform is added to the master parents set as it will intialise it's parent to null
void Transform::OnDestroy () {
	for (Transform* child : this->children) {
		child->SetParent(0); //Nulls all children parents
	}
	this->SetParent(0);//Sets the current parent to null to remove it's refrence from the parent
	masterParents.erase(this); //Remove it's in the master parent. 
}
void Transform::SetParent(Transform* parent) {
	if (this->parent != 0)
		this->parent->RemoveChild(this);//If the parent isn't null than we tell the parent that we are no longer children of it
	else
		masterParents.erase(this); //Other wise we remove ourselves from the master list (as we were in that list before if we had no parent)

	this->parent = parent;
	if (parent != 0)
		parent->SetChild(this);	//Set the Transform to be the child of the new parent
	else
		masterParents.insert(this); //Other wise we insert ourselves back on the master list (as we have no parents now :(   )
}
void Transform::Render () {
	//Renders Transform and it's children itself
	//Pushes the transforms matrix

	this->PushTransformMatrix();
	for (Renderer* renderer : this->gameObject->renderers) {
		renderer->Render();//Calls Render on the mesh so it renders it's mesh
	}

	for(Transform* child : this->children) {
		if (child != 0) {
			child->Render();//Calls render on all of the children before popping back the matrix.
		}
	}
	glPopMatrix ();
}
void Transform::CopyValues(Transform* transform) {
	this->SetParent(transform->parent);
	this->localPos 		= transform->localPos;
	this->localRotation = transform->localRotation;
	this->localScale 	= transform->localScale;
} //Copies the values of another transform
void Transform::PushTransformMatrix() {
	glPushMatrix();
	//Push the matrix, than translate, rotate, scale
	glTranslatef (this->localPos.x, this->localPos.y, this->localPos.z);

	glm::quat localRotation = this->localRotation;
	localRotation.w *= -1;

	glm::mat4x4 rotation = glm::mat4_cast(localRotation);
	glMultMatrixf(glm::value_ptr(rotation));
	glScalef (this->localScale.x, this->localScale.y, this->localScale.z);

	//Notice not popping, this is used by a rendering function, that function will handle the popping
}//No need for a pop version, no information is needed from the specific transform.

glm::vec3 Transform::GetForward() {
	return glm::vec3(0, 0, 1) * this->localRotation;
}
glm::vec3 Transform::GetUp() {
	return glm::vec3(0, 1, 0) * this->localRotation;
}
glm::vec3 Transform::GetRight() {
	return glm::vec3(1, 0, 0) * this->localRotation;
}
void Transform::LookAt (glm::vec3 pos, glm::vec3 up) {
	glm::mat4 rotMatrix = glm::lookAt(this->localPos, pos, up);
	localRotation = glm::quat_cast(rotMatrix);
}	//Sets the rotation to look at a certain point