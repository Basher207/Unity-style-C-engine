#include "MeshRenderer.hpp"
#include "glad.h"
#include <stdio.h>
#include <vector>
#include <stdio.h>

void MeshRenderer::Render () {//Renders itself
	glColor3f (this->color.x, this->color.y, this->color.z);//Sets the current drawnig color
	this->mesh.Render();//Calls Render on the mesh so it renders
}
