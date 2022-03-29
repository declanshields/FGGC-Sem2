#pragma once
#include "Vector3D.h"
#include "Consts.h"
#include "ParticleModel.h"

class RigidBody : ParticleModel
{
private:
	Vector3D CalculateTorque(Vector3D force, Vector3D position);

	DirectX::XMFLOAT3X3 InertiaTensor;
};

