#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <string.h>
#include <glm/vec2.hpp>

//Some useful macros to access the input data
#define OnKeyDown(k) (Input::keys[k]&&!Input::previous_keys[k])
#define OnKeyUp(k) (!Input::keys[k]&&Input::previous_keys[k])
#define OnKey(k) (Input::keys[k])
#define OnMouseButton(n) (Input::mouse_state&SDL_BUTTON(n))

namespace Input {
	extern glm::vec2 mouse_screen_pos;		//Mouse current pos
	extern glm::vec2 mouse_prev_screen_pos;	//Mouse pos in the previous frame
	extern glm::vec2 mouse_delta_pos;		//current pos - prev pos
	extern int mouse_state;					//Mouse state, used for mouse button checking
	extern const uint8_t* keys;				//List of keys inputs
	extern int number_of_keys;				//Number of keys grabbed (passed by SDL_GetKeyboardState)
	extern uint8_t* previous_keys;			//Keys pressed in the previous frames, (used KeyDown and KeyUp checking)
	extern void Input_Update ();			//Updates input data
};