#pragma once
#include <Engine.hpp>

class Gun : public MonoBehaviour {
public:
	int frameOfNextShot; //Frame of the frame till 
	bool nextShotLeft;	 //Used to alternate shots left to right
	void Update();
};