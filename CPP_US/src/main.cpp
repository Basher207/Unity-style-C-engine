#include <Engine.hpp>
#include "MovementScript.hpp"
#include "Gun.hpp"
#include "Animations.hpp"

int main () {
	InitEngine(); //Intializes all the engine variables and creates the window

	Camera::mainCamera->gameObject->AddComponent<MovementScript>();//Adds Movementscript to the camera gameObject
	Camera::mainCamera->gameObject->AddComponent<Gun>();		   //Adds GunScript to the camera 


	//Creates a renderer for the ground, scales and positions it to look like such
	GameObject* ground = new GameObject();//Creates a new GameObject for the ground
	ground->AddComponent<MeshRenderer>()->color = glm::vec3(0.1, 0.6, 0.1); //Adds a MeshRenderer script to the ground, and sets it's color
	ground->transform.localPos = glm::vec3( 0, -3, 0); //Sets local position of the ground to slightly below the player
	ground->transform.localScale = glm::vec3(-10000, 0.1, 10000); //Sets it's scale.


	GameObject* sun = new GameObject();	//Creates a sun object
	sun->AddComponent<MeshRenderer>()->color = glm::vec3(1,1,0);
	sun->transform.localPos = glm::vec3( 0, 1000, 0);
	sun->transform.localScale = glm::vec3( 200, 200, 200);

	RunEngineLoop();
}