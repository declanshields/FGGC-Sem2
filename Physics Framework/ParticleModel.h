#pragma once
#include "Vector3D.h"
#include "Consts.h"

class GameObject;
class Particle;

class ParticleModel
{
private:
	GameObject* thisObject    = nullptr;
	Particle*   thisParticle  = nullptr;
	Vector3D    velocity      = { 0.0f, 0.0f, 0.0f };
	Vector3D    acceleration  = { 0.0f, 0.0f, 0.0f };

	//forces
	Vector3D thrust   = { 0.0f, 0.0f, 0.0f };
	Vector3D netForce = { 0.0f, 0.0f, 0.0f };
	Vector3D lift     = { 0.0f, 0.0f, 0.0f };
	Vector3D drag     = { 0.0f, 0.0f, 0.0f };

	float mass        = 0.0f;
	float dragFactor  = 2.5f;
	float deadZone    = 0.005f;

	bool laminar      = true;
	bool flying       = false;

	float boundingSphereRadius;
public:
	ParticleModel(Vector3D vel, Vector3D acc, float m);
	~ParticleModel();

	//Get Methods
	Vector3D GetVelocity()     { return velocity; }
	Vector3D GetAcceleration() { return acceleration; }
	float    GetMass()         { return mass; }
	float    GetRadius()       { return boundingSphereRadius; }
	bool     GetFlying()       { return flying; }
	bool     GetLaminar()      { return laminar; }

	//Set Methods
	void SetMass         (float m)            { mass = m; }
	void SetThrust       (Vector3D _thrust)   { thrust = _thrust; }
	void SetLift         (Vector3D _lift)     { lift = _lift; }
	void SetObject       (GameObject* object) { thisObject = object; }
	void SetParticle     (Particle* particle) { thisParticle = particle; }
	void SetAcceleration (Vector3D acc)       { acceleration = acc; }
	void SetVelocity     (Vector3D vel)       { velocity = vel; }
	void SetLaminar      (bool _laminar)      { laminar = _laminar; }
	void SetBSRadius     (float radius)       { boundingSphereRadius = radius; }
	void SetFlying       (bool fly)           { flying = fly; }

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