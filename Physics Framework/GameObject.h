#pragma once

#include <directxmath.h>
#include <d3d11_1.h>

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
	GameObject(Transform* transform, Appearance* appearance, ParticleModel* particleModel);
	~GameObject();

	Transform* GetTransform() const { return _transform; }
	Appearance* GetAppearance() const { return _appearance; }
	ParticleModel* GetParticleModel() const { return _particleModel; }

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	Transform* _transform;
	Appearance* _appearance;
	ParticleModel* _particleModel;
};

