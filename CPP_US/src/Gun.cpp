#include "Gun.hpp"
#include "RigidBody.hpp"

RigidBody* MakeBullet () {
	GameObject* bulletGO = new GameObject();//Create a new GameObject for the bullet
	bulletGO->AddComponent<MeshRenderer>(); //Adds a renderer to the bullet object
	bulletGO->transform.localScale = glm::vec3(0.2, 0.2, 0.2); //Scales the bullet
	return bulletGO->AddComponent<RigidBody>(); //Adds a rigidbody to make it move and fall
}
void Gun::Update () {
	//Only shoot if enough time has ellapsed
	if (frameOfNextShot < frameCount && OnMouseButton(SDL_BUTTON_LEFT)) { //and left mouse button is down
		frameOfNextShot = frameCount + 5; //Time of next shot is 5 frames ahead from the moment of the last shot
		RigidBody* rigid = MakeBullet();  //Make a new bullet object
		rigid->vel =-this->transform->GetForward(); //Sets the velocity to forward
		rigid->transform->localRotation = this->transform->localRotation;
		rigid->transform->localPos = transform->localPos + this->transform->GetUp() * -0.4f;
		rigid->transform->localPos+= this->transform->GetRight() * (this->nextShotLeft ? 1.0f : -1.0f);
		this->nextShotLeft = !this->nextShotLeft;
	}
}