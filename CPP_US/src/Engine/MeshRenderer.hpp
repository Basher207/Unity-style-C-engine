#pragma once
#include "Mesh.hpp"
#include "Transform.hpp"
#include "MonoBehaviour.hpp"
#include "GameObject.hpp"

class MeshRenderer : public Renderer {
public:
	glm::vec3 color; //Color to set before rendering
	Mesh mesh;		 //Mesh to be rendererd

	void Render();
};