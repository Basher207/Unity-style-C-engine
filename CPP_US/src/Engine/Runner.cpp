#include <SDL2/SDL.h>
#include "glad.h"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Input.hpp"
#include "Math.hpp"

#include <stdio.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <math.h>

static const int SCREEN_FULLSCREEN = 0;
static const int SCREEN_WIDTH = 1400;
static const int SCREEN_HEIGHT = 1000;
static SDL_Window *window = NULL;
static SDL_GLContext maincontext;



int frameCount = 0;
void sdl_die (const char* message) {
	printf ("%s: %s\n", message, SDL_GetError ());
	exit (2);
}
//NOTE:
//Some of the stuff to setup the SDL opengl window (Only in the function init_screen) environment were originally adabted from this tutorial
//
//https://bcmpinc.wordpress.com/2015/08/18/creating-an-opengl-4-5-context-using-sdl2-and-glad/
//
//However it has been adapted and altered betewen a bunch of programs that i've made in the past
//I have gone through the references of every function and am familiar with everything it's calling.
//These two functions (sdl_die, and init_screen) are the only functions that are taken from anywhere.
//Everything else is written by me (in src).
void init_screen (const char* caption) {
	SDL_GL_LoadLibrary(NULL);//Passing the default opengl library(no need to specify)

	// SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 32);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		sdl_die ("Couldn't load intialize SDL");
	
	if (SCREEN_FULLSCREEN) {
		window = SDL_CreateWindow (caption,
								   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	} else {
		window = SDL_CreateWindow (caption,
								   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	}
	if (window == NULL) sdl_die ("Couldn't set video mode");

	maincontext = SDL_GL_CreateContext(window);
	if (maincontext == NULL)
		sdl_die ("Failed to create opengl context");
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	int w, h;
	SDL_GetWindowSize (window, &w, &h);
	glViewport (0, 0, w, h);
	glClearColor (0.0f, 0.5f, 1.0f, 0.0f);
}



//Rest is original

void InitEngine() {
	init_screen("3D Bash example");

	// SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);



	glPushMatrix(); //Push the matrix
	//Scale the screne by the aspect ratio of the screen
    float widthScaling = (float)SCREEN_HEIGHT / SCREEN_WIDTH;
    glScalef(widthScaling, 1, 1);

    Camera::StartCamera();
}
void RunEngineLoop () {
	SDL_Event event;
	bool quit;
	
	Input::Input_Update();//Updates input data before the start to prevent intial position of the mouse to mess with the beginning of the game
	while (!quit) {
		Input::Input_Update();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT); //Clears the current render texture (with the glClearColor set after creating the window)
		glClear(GL_DEPTH_BUFFER_BIT); //Clears the depth buffer, if not done you can't update any pixel unless that fragment was closer than the last 
									  //fragment that drew on that pixel
		if (Input::keys[SDL_SCANCODE_ESCAPE]) //If escape is inputed quit the game loop
			break;



        GameObject::UpdateFrame(); //Does a frame logic
        Camera::mainCamera->Render(); //Renders the frame from the perspective of the camera 

		SDL_GL_SwapWindow(window);//Swaps buffers
        SDL_Delay(20);//Delay of 20ms for 50 frames per second
        frameCount++;//Frame counter increment
	}
	glPopMatrix();//Pops the screen scale matrix
}








