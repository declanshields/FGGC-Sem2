#include "ParticleModel.h"
#include "GameObject.h"

ParticleModel::ParticleModel(Vector3D vel, Vector3D acc, float m) 
{
	velocity = vel;
	acceleration = acc;
	netForce = Vector3D();
	mass = m;
}

ParticleModel::~ParticleModel() 
{
    if(thisObject != nullptr)
	{
		delete thisObject;
		thisObject = nullptr;
	}
}

void ParticleModel::MoveConstVelocity(float t)
{
	//Update position
	Vector3D position = thisObject->GetTransform()->GetPosition();
	thisObject->GetTransform()->SetPosition(position + (velocity * t));
}

void ParticleModel::MoveConstAcceleration(float t)
{
	//Update position
	Vector3D position = thisObject->GetTransform()->GetPosition();
	thisObject->GetTransform()->SetPosition(position + (velocity * t));

	//Update velocity
	velocity = velocity + (acceleration * t);
}

void ParticleModel::UpdateNetForce()
{
	//Calculate external net force
	netForce.y = -gravity;
}

void ParticleModel::UpdateAccel()
{
	//Calculate acceleration by net external force
	acceleration.x = netForce.x / mass;
	acceleration.y = netForce.y / mass;
	acceleration.z = netForce.z / mass;
}

void ParticleModel::Move()
{
	
}