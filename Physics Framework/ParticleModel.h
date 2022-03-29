#pragma once
#include "Vector3D.h"
#include "Consts.h"

class GameObject;
class Particle;

class ParticleModel
{
private:
	GameObject* thisObject    = nullptr;
	Vector3D    velocity      = { 0.0f, 0.0f, 0.0f };
	Vector3D    acceleration  = { 0.0f, 0.0f, 0.0f };

	//forces
	Vector3D thrust   = { 0.0f, 0.0f, 0.0f };
	Vector3D netForce = { 0.0f, 0.0f, 0.0f };
	Vector3D lift     = { 0.0f, 0.0f, 0.0f };
	Vector3D drag     = { 0.0f, 0.0f, 0.0f };

	float mass            = 0.0f;
	float dragFactor      = 0.0f;
	float collisionRadius = 0.0f;

	bool laminar      = false;
public:
	ParticleModel(Vector3D vel, Vector3D acc, float m);
	~ParticleModel();

	//Get Methods
	Vector3D GetVelocity()     { return velocity; }
	Vector3D GetAcceleration() { return acceleration; }
	float    GetMass()         { return mass; }
	float    GetRadius()       { return collisionRadius; }

	//Set Methods
	void SetMass         (float m)            { mass = m; }
	void SetThrust       (Vector3D _thrust)   { thrust = _thrust; }
	void SetLift         (Vector3D _lift)     { lift = _lift; }
	void SetObject       (GameObject* object);
	void SetAcceleration (Vector3D acc)       { acceleration = acc; }
	void SetVelocity     (Vector3D vel)       { velocity = vel; }
	void SetLaminar      (bool _laminar)      { laminar = _laminar; }
	void SetRadius		 (float radius)		  { collisionRadius = radius; }

	//Movement Methods
	void Lift(float t);
	void Move(float t);
	void MoveConstVelocity(float t);
	void MoveConstAcceleration(float t);
	void MotionInFluid(float t);
	void DragForce();
	void DragLaminarFlow();
	void DragTurbulentFlow();

	//Update Methods
	void UpdateState(float t);
	void UpdateNetForce();
	void UpdateAccel();
	bool CollisionCheck(Vector3D position, float radius);
};