#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MonoBehaviour.hpp"

class Camera : public MonoBehaviour {//The camera is a mono behavior and is a component of gameobject like everything else
public:
	static Camera* mainCamera; //A singlton of the active camera
	static Camera* StartCamera (); //Intializes the camera and returns an instance of it


	//The perspective matrix, to be used as the base matrix for the rendering
	const glm::mat4 perspective_mat = glm::perspective(glm::radians(75.0f), 1.0f, 1.0f, 20000.0f);

	void Awake ();
	void Render (); //Renders the scene from the perspective of the camera
};