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
	XMFLOAT4X4 _world;

public:
	Transform(Vector3D position, Vector3D rotation, Vector3D scale);
	Transform();
	~Transform();

	//Set and get for transformation
	void SetPosition(Vector3D position) { _position = position; }
	Vector3D GetPosition() const { return _position; }

	void SetScale(Vector3D scale) { _scale = scale; }
	Vector3D GetScale() const { return _scale; }

	void SetRotation(Vector3D rotation) { _rotation = rotation; }
	Vector3D GetRotation() const { return _rotation; }

	void SetWorldMatrix(XMMATRIX worldMatrix) { XMStoreFloat4x4(&_world, worldMatrix); }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
};

