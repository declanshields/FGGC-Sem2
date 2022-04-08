#pragma once

#include <d3d11_1.h>
#include<DirectXMath.h>
#include "Vector3D.h"
#include "Quaternion.h"

using namespace DirectX;

class Transform
{
private:
	Vector3D _position;
	Vector3D _rotation;
	Vector3D _scale;
	Vector3D _angularVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3D _angularAcceleration = { 0.0f, 0.0f, 0.0f };

	Transform* _parent = nullptr;
	Quaternion _qRotation = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4X4 _world;
	Vector3D _centerOfMass;
	float _crossSectionalArea;

	bool _fixed = false;

public:
	Transform(Vector3D position, Vector3D rotation, Vector3D scale);
	Transform();
	~Transform();

	//Set Methods
	void SetPosition(Vector3D position) { _position = position; }
	void SetScale(Vector3D scale);
	void SetRotation(Vector3D rotation) { _rotation = rotation; }
	void SetWorldMatrix(XMMATRIX worldMatrix) { XMStoreFloat4x4(&_world, worldMatrix); }
	void SetCenterOfMass(Vector3D _com) { _centerOfMass = _com; }
	void SetParent(Transform* parent) { _parent = parent; }
	void SetAngularVelocity(Vector3D aVel) { _angularVelocity = aVel; }
	void SetAngularAcceleration(Vector3D aAcc) { _angularAcceleration = aAcc; }
	void SetFixed(bool fixed) { _fixed = fixed; }

	//Get Methods
	Vector3D GetCenterOfMass() { return _centerOfMass; }
	float GetCrossSection() { return _crossSectionalArea; }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	Vector3D GetRotation() const { return _rotation; }
	Vector3D GetScale() const { return _scale; }
	Vector3D GetPosition() const { return _position; }

	void Update(float t);
};

