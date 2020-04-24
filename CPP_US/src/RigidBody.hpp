#pragma once
#include <Engine.hpp>
#include <unordered_set>

class RigidBody : public MonoBehaviour {
public:
	std::unordered_set<RigidBody*> rigidBods;

	glm::vec3 vel;
	int deathFrame;
	void Start();
	void Update();
	void OnDestroy();
};