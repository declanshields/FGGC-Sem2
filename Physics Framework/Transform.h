#pragma once

#include <d3d11_1.h>
#include<DirectXMath.h>
#include "Vector3D.h"

using namespace DirectX;

class Transform
{
private:
	Vector3D _position;
	Vector3D _rotation;
	Vector3D _scale;
	Transform* _parent = nullptr;
	XMFLOAT4X4 _world;
	Vector3D _centerOfMass;

public:
	Transform(Vector3D position, Vector3D rotation, Vector3D scale);
	Transform();
	~Transform();

	//Set and get for transformation
	void SetPosition(Vector3D position) { _position = position; }
	Vector3D GetPosition() const { return _position; }

	void SetScale(Vector3D scale);
	Vector3D GetScale() const { return _scale; }

	void SetRotation(Vector3D rotation) { _rotation = rotation; }
	Vector3D GetRotation() const { return _rotation; }

	void SetWorldMatrix(XMMATRIX worldMatrix) { XMStoreFloat4x4(&_world, worldMatrix); }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void Update(float t);

	void SetParent(Transform* parent) { _parent = parent; }

	void SetCenterOfMass(Vector3D _com) { _centerOfMass = _com; }
	Vector3D GetCenterOfMass() { return _centerOfMass; }
};

