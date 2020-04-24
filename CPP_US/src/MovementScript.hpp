#pragma once

#include <Engine.hpp>

class MovementScript : public MonoBehaviour {
	//The position and cameras forward (looking direction)
	//This is used to calculate the projection matrix.
	glm::vec3 pos;
	glm::vec3 forward;

	void Translate (float moveX, float moveZ);
	void Rotate (int rotateX, int rotateY);

	void Awake ();
	void Update ();
};