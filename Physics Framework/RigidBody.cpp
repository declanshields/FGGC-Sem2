#include "RigidBody.h"

Vector3D RigidBody::CalculateTorque(Vector3D force, Vector3D position)
{
	Vector3D torque = position.Cross(force);
	return torque;
}
