#pragma once
#include "Vector3D.h"
#include "Consts.h"

class GameObject;

class ParticleModel
{
private:
	GameObject* thisObject = nullptr;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D netForce;
	float mass;

	//TODO
	//friction, thrust, brake force

public:
	ParticleModel(Vector3D vel, Vector3D acc, float m);
	~ParticleModel();

	void MoveConstVelocity(float t);
	void MoveConstAcceleration(float t);

	Vector3D GetVelocity() { return velocity; }
	void SetVelocity(Vector3D vel) { velocity = vel; }

	Vector3D GetAcceleration() { return acceleration; }
	void SetAcceleration(Vector3D acc) { acceleration = acc; }

	float GetMass() { return mass; }
	void SetMass(float m) { mass = m; }

	void SetObject(GameObject* object) { thisObject = object; }

	void UpdateState(float t);
	void UpdateNetForce();
	void UpdateAccel();
	void Move(float t);
};