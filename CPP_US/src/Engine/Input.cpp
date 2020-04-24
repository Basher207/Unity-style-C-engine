#include <Input.hpp>




//Assigns all the memroy for all the Input data

glm::vec2	Input::mouse_screen_pos (0.);
glm::vec2	Input::mouse_prev_screen_pos (0.);
glm::vec2	Input::mouse_delta_pos (0.);

int 		Input::mouse_state		= 0;
const uint8_t*	Input::keys 		= 0;
int 		Input::number_of_keys	= 0;
uint8_t mem_for_prev_keys [5000] = {};
uint8_t*	Input::previous_keys	= mem_for_prev_keys;

void Input::Input_Update () {
	if (Input::keys != 0)
		memcpy(Input::previous_keys, Input::keys, Input::number_of_keys); //Copies current keys to previous keys
	SDL_PumpEvents(); //Pumps new events
	Input::keys = SDL_GetKeyboardState(&Input::number_of_keys); //Assigns new keys states

    int32_t x, y; 
    Input::mouse_state = SDL_GetMouseState(&x, &y); //Gets the mouse positions and stores the state

    Input::mouse_prev_screen_pos = Input::mouse_screen_pos; //Stores positions into the Input:: data
    Input::mouse_screen_pos.x = x;
    Input::mouse_screen_pos.y = y;
    Input::mouse_delta_pos = Input::mouse_screen_pos - Input::mouse_prev_screen_pos; //Sets } as the delta
}