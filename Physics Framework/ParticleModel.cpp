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

void ParticleModel::Lift(float t)
{
	Vector3D weight = { 0.0f, -(mass * gravity), 0.0f };
	Vector3D upForce;

	if (thisObject->GetTransform()->GetPosition().y >= 0.5f)
		upForce = { 0.0f, 0.0f, 0.0f };
	else
	{
		upForce = weight;
		upForce.y = -upForce.y;
	}

	netForce = netForce + upForce;

	UpdateState(t);
}


void ParticleModel::UpdateNetForce()
{
	//Calculate external net force

	//Add weight if applicable
	if (thisObject->GetTransform()->GetPosition().y > 0.5f)
		netForce.y = netForce.y - (mass * gravity);

	netForce = netForce + thrust;
	netForce = netForce + lift;
	netForce = netForce + drag;

	//calculate friction if thrust is > 0
	if (thrust.x != 0 || thrust.y != 0 || thrust.z != 0)
	{
		float normalForce = mass * gravity;
		float frictionForce = normalForce * concrete;

		if (thrust.x != 0)
		{
			if (thrust.x > 0)
			{
				if (thrust.x - frictionForce >= 0)
					netForce.x += (thrust.x - frictionForce);
			}
			else
			{
				if (thrust.x + frictionForce <= 0)
					netForce.x -= (thrust.x + frictionForce);
			}
		}

		if (thrust.y != 0)
		{
			if (thrust.y > 0)
			{
				if (thrust.y - frictionForce >= 0)
					netForce.y += (thrust.y - frictionForce);
			}
			else
			{
				if (thrust.y + frictionForce <= 0)
					netForce.y -= (thrust.y + frictionForce);
			}
		}

		if (thrust.z != 0)
		{
			if (thrust.z > 0)
			{
				if (thrust.z - frictionForce >= 0)
					netForce.z += (thrust.z - frictionForce);
			}
			else
			{
				if (thrust.z + frictionForce <= 0)
					netForce.z -= (thrust.z + frictionForce);
			}
		}
	}
}

void ParticleModel::UpdateAccel()
{
	//Calculate acceleration by net external force

	//if 0/infinite mass
	if (mass != 0.0f) 
	{
		acceleration.x = netForce.x / mass;
		acceleration.y = netForce.y / mass;
		acceleration.z = netForce.z / mass;
	}
	else
	{
		acceleration = Vector3D(0.0f, 0.0f, 0.0f);
	}
}

void ParticleModel::Move(float t)
{
	//check to see if object shouldn't move
	if (mass == 0.0f)
		return;

	//update world position
	Vector3D position = thisObject->GetTransform()->GetPosition();

	position.x = position.x + velocity.x * t + 0.5 * acceleration.x * t * t;
	position.y = position.y + velocity.y * t + 0.5 * acceleration.y * t * t;
	position.z = position.z + velocity.z * t + 0.5 * acceleration.z * t * t;

	if (position.y <= 0.5f)
		position.y = 0.5f;

	//update velocity
	velocity.x = velocity.x + acceleration.x * t;
	velocity.y = velocity.y + acceleration.y * t;
	velocity.z = velocity.z + acceleration.z * t;

	thisObject->GetTransform()->SetPosition(position);

	Debug::DebugMsg(position);
}

void ParticleModel::UpdateState(float t)
{
	//Calculate external net force
	UpdateNetForce();

	//Update acceleration of object using Newton's second law of motion
	UpdateAccel();

	//Update world position and velocity
	Move(t);
}

void ParticleModel::MotionInFluid(float t)
{
	DragForce();
	UpdateState(t);
}

void ParticleModel::DragForce()
{
	if(laminar)
	{
		DragLaminarFlow();
	}
	else
	{
		DragTurbulentFlow();
	}
}

void ParticleModel::DragLaminarFlow()
{
	dragFactor = 0.5f * air_density * (velocity.CalcMagnitude() * velocity.CalcMagnitude()) * cube_damping * thisObject->GetTransform()->GetCrossSection();

	drag.x = -dragFactor * velocity.x;
	drag.y = -dragFactor * velocity.y;
	drag.z = -dragFactor * velocity.z;
}

void ParticleModel::DragTurbulentFlow()
{
	dragFactor = 0.5f * air_density * (velocity.CalcMagnitude() * velocity.CalcMagnitude()) * cube_damping * thisObject->GetTransform()->GetCrossSection();

	float velocityMagnitude = velocity.CalcMagnitude();
	Vector3D unitVelocity;
	velocity.Normalize();
	unitVelocity = velocity;

	float dragMagnitude = dragFactor * velocityMagnitude * velocityMagnitude;

	drag.x = -dragMagnitude * unitVelocity.x;
	drag.y = -dragMagnitude * unitVelocity.y;
	drag.z = -dragMagnitude * unitVelocity.z;
}
