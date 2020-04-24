#include "Animations.hpp"

void RotateOverTime::Update () {
	this->transform->localRotation += this->rotOverTime; //Rotates by rotOverTime every frame
}