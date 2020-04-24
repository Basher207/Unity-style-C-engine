
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "glad.h"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"

//The verts store all the vertex's that makeup the cube
//Note i'm aware I can use the same vertex multiple times 
//By calling it at different times
//But I used a script to debug out mesh's in Unity
//To this format below, so I can get any mesh I want without having to 
//type stuff maully
//And this is the mesh that they use (I believe it's to prevent corner interpulation in shaders)
//Eeventually something I can play around with.

const glm::vec3 verts [] = {
	glm::vec3 ( 1.0 ,-1.0 , 1.0)	,glm::vec3 (-1.0 ,-1.0 , 1.0),
	glm::vec3 ( 1.0 , 1.0 , 1.0)	,glm::vec3 (-1.0 , 1.0 , 1.0),
	glm::vec3 ( 1.0 , 1.0 ,-1.0)	,glm::vec3 (-1.0 , 1.0 ,-1.0),
	glm::vec3 ( 1.0 ,-1.0 ,-1.0)	,glm::vec3 (-1.0 ,-1.0 ,-1.0),
	glm::vec3 ( 1.0 , 1.0 , 1.0)	,glm::vec3 (-1.0 , 1.0 , 1.0),
	glm::vec3 ( 1.0 , 1.0 ,-1.0)	,glm::vec3 (-1.0 , 1.0 ,-1.0),
	glm::vec3 ( 1.0 ,-1.0 ,-1.0)	,glm::vec3 ( 1.0 ,-1.0 , 1.0),
	glm::vec3 (-1.0 ,-1.0 , 1.0)	,glm::vec3 (-1.0 ,-1.0 ,-1.0),
	glm::vec3 (-1.0 ,-1.0 , 1.0)	,glm::vec3 (-1.0 , 1.0 , 1.0),
	glm::vec3 (-1.0 , 1.0 ,-1.0)	,glm::vec3 (-1.0 ,-1.0 ,-1.0),
	glm::vec3 ( 1.0 ,-1.0 ,-1.0)	,glm::vec3 ( 1.0 , 1.0 ,-1.0),
	glm::vec3 ( 1.0 , 1.0 , 1.0)	,glm::vec3 ( 1.0 ,-1.0 , 1.0)
};
//The tris indicate the index's of verticies in the order that they should be called to sucessfully render the scene
const uint32_t tris [] = {
	0,2,3,0,3,1,
	8,4,5,8,5,9,
	10,6,7,10,7,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23
};
//Since it's only one mesh for now these don't need to be object specific or accessed from outside of here.
GLuint boxVertsId = 0;//Key used for mesh verts
GLuint boxTrisId = 0; //Key used for mesh tris


Mesh::Mesh () {
	if (!boxVertsId || !boxTrisId) { //Only need the one mesh
		GLfloat glFloatVerts[sizeof(verts)/sizeof(verts[0])*3]; //GLFloats array used to pass the mesh Data into the glBuffer
		for (int i = 0; i < sizeof(verts)/sizeof(verts[0]); i++) {
			int glFloatIndex = i * 3;
			glFloatVerts[glFloatIndex + 0] = verts[i].x;
			glFloatVerts[glFloatIndex + 1] = verts[i].y;
			glFloatVerts[glFloatIndex + 2] = verts[i].z;
		}
		glGenBuffers(1, &boxVertsId);//Generates 1 buffer for the verts
		glBindBuffer(GL_ARRAY_BUFFER, boxVertsId); //Marks the buffer as an array buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(glFloatVerts), &glFloatVerts, GL_STATIC_DRAW); // Copies the buffer data from glFloatVerts

		glGenBuffers(1, &boxTrisId);//Generates 1 buffer for the tri call indicies
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxTrisId);//Marks the buffer as an array buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tris), &tris, GL_STATIC_DRAW); //Copies the tri data
	}
}
void Mesh::Render () {
	glBindBuffer(GL_ARRAY_BUFFER, boxVertsId); //Binds the box vert id for rendering 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxTrisId); //Binds the box tris array as the element indicies

	glEnableClientState(GL_VERTEX_ARRAY); //Enables the client state that will be used for rendering
	glVertexPointer(3, GL_FLOAT, 0, 0);   //Sets Sets the type of data that was stored in the array, and the number of dimensions

	glDrawElements(GL_TRIANGLES, sizeof(tris)/sizeof(tris[0]), GL_UNSIGNED_INT, 0); //Sets the drawing type, and the size of the array, and passes in the type of data
																					//Stored in the boxTrisId

	glDisableClientState(GL_VERTEX_ARRAY);											//Post rendering disables the rendering client

	glBindBuffer(GL_ARRAY_BUFFER, 0);												//Sets buffers to null
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);										//Sets buffers to null
}