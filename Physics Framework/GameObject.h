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
	GameObject(Transform* transform, Appearance* appearance, ParticleModel* particleModel, const Vector3D startPosition);
	~GameObject();

	Transform*     GetTransform()     const { return _transform; }
	Appearance*    GetAppearance()    const { return _appearance; }
	ParticleModel* GetParticleModel() const { return _particleModel; }

	float GetLifespan()              { return _lifespan; }
	void  SetLifespan(float newSpan) { _lifespan = newSpan; }

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	Transform*     _transform;
	Appearance*    _appearance;
	ParticleModel* _particleModel;

	float _lifespan = 0.0f;
};

