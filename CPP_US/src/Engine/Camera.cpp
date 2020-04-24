#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "GameObject.hpp"
#include "Transform.hpp"
#include "glad.h"
#include "Camera.hpp"

//Allocating memory for the singleton 
Camera* Camera::mainCamera;

Camera* Camera::StartCamera () {
	if (!Camera::mainCamera) {//If camera is already started dont create a new one
		GameObject* camObject = new GameObject(); //Create a new GameObject to hold the camera
		camObject->AddComponent<Camera>(); //Add a camera MonoBehavior to the camObject, and stors it in the mainCamera singlton
	}
	return mainCamera; //Return the mainCamera
}
void Camera::Awake () { 
	mainCamera = this; //On camera object Awake, stores itself as the camera singlton
}

void Camera::Render () {
    glPushMatrix(); //Pushes the matrix in preperations for rendering

    // glMultMatrix takes in a float* to a matrix array
    // glm::value_ptr returns such a pointer 
    glMultMatrixf(glm::value_ptr(this->perspective_mat));

    //Turns the quaternion rotation into a matrix for multiplications
	glm::mat4x4 rotation = glm::mat4_cast(transform->localRotation);
	glMultMatrixf(glm::value_ptr(rotation)); 
	//Translates the camera by it's position
	glTranslatef (-this->transform->localPos.x,-this->transform->localPos.y,-this->transform->localPos.z);


	//Start rendering all transforms.
    Transform::RenderMasterParents();

    glPopMatrix();//Pop the matrix
}