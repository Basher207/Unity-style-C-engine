#include "RigidBody.hpp"

void RigidBody::Start () {
	deathFrame = frameCount + 200;
	rigidBods.insert(this);
}
void RigidBody::Update () {
	this->transform->localPos += this->vel;
	this->vel += glm::vec3(0, -0.005f, 0);
	if (this->deathFrame < frameCount)
		this->gameObject->Destroy();
}
void RigidBody::OnDestroy() {
	rigidBods.erase(this);
}