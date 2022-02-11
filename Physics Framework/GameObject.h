#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Vector3D.h"
#include "Debug.h"

#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"

using namespace DirectX;
using namespace std;


class GameObject
{
public:
	GameObject(string type, Transform* transform, Appearance* appearance);
	~GameObject();

	Transform* GetTransform() const { return _transform; }
	Appearance* GetAppearance() const { return _appearance; }

	string GetType() const { return _type; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	Transform* _transform;
	Appearance* _appearance;
	ParticleModel* _particleModel;

	string _type;

	ID3D11ShaderResourceView * _textureRV;

	GameObject * _parent;
};

