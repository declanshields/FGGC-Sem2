#pragma once
#include "Vector3D.h"
#include "Consts.h"

class GameObject;

class ParticleModel
{
private:
	GameObject* thisObject = nullptr;
	Vector3D velocity      = { 0.0f, 0.0f, 0.0f };
	Vector3D acceleration  = { 0.0f, 0.0f, 0.0f };

	//forces
	Vector3D thrust   = { 0.0f, 0.0f, 0.0f };
	Vector3D netForce = { 0.0f, 0.0f, 0.0f };
	Vector3D lift     = { 0.0f, 0.0f, 0.0f };

	float mass = 0.0f;

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

	void SetThrust(Vector3D _thrust) { thrust = _thrust; }
	void SetLift(Vector3D _lift) { lift = _lift; }

	void SetObject(GameObject* object) { thisObject = object; }

	void UpdateState(float t);
	void UpdateNetForce();
	void UpdateAccel();
	void Move(float t);
};