#pragma once
#include <Engine.hpp>

class RotateOverTime : public MonoBehaviour {
public:
	glm::quat rotOverTime;

	void Update();
};