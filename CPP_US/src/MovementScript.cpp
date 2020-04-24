#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MovementScript.hpp"
#include <Engine.hpp>

#include <stdio.h>

void MovementScript::Awake () {
	this->pos = transform->localPos;
	this->forward = glm::vec3(0., 0, 1.);
}
void MovementScript::Rotate (int rotateX, int rotateY) {
	this->forward = glm::rotateY(this->forward,-rotateX * 0.01f);
	//By getting the cross product of the forward vector and the up vector ill
	//get a vector perpendicular to both. This would be the desired vector to rotate around
	//when looking up and down.
	glm::vec3 yRotationAxis = glm::cross (this->forward, glm::vec3(0, 1, 0));
	yRotationAxis = glm::normalize (yRotationAxis);

	this->forward = glm::rotate (this->forward,-rotateY * 0.01f ,yRotationAxis);
	transform->LookAt(transform->localPos + this->forward);
}
void MovementScript::Translate (float moveX, float moveZ) {
	glm::vec3 movementForward = this->forward;
	movementForward.y = 0;//To prevent movement due to looking up
	movementForward = glm::normalize (movementForward); //Make's sure it's normalized so you don't move less if you are looking up

	this->pos += movementForward * moveZ;

	glm::vec3 side = glm::cross(movementForward, glm::vec3(0, 1, 0)); //A cross product of forward and up would give me a perpendicular vector to use for side movement.
	side = glm::normalize(side);//Again normalized to make sure speed consistency

	this->pos += side *-moveX;
	transform->localPos = this->pos;
}
void MovementScript::Update () {
	float moveX = 0, moveZ = 0;
	float moveSpeed = Input::keys[SDL_SCANCODE_LSHIFT] ? 1 : 0.5;
	if (Input::keys[SDL_SCANCODE_W]) {
		moveZ += moveSpeed;
	}
	if (Input::keys[SDL_SCANCODE_S]) {
		moveZ -= moveSpeed;
	}
	if (Input::keys[SDL_SCANCODE_D]) {
		moveX -= moveSpeed;
	}
	if (Input::keys[SDL_SCANCODE_A]) {
		moveX += moveSpeed;
	} //Adds all the input movenets than applies the movenet to the transform through the Translate and Rotate functions
	this->Translate(moveX, moveZ);
    this->Rotate(Input::mouse_delta_pos.x, Input::mouse_delta_pos.y);
}