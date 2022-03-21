#pragma once

#include <DirectXMath.h>
#include <d3d11_1.h>

#include "Vector3D.h"
#include "Debug.h"

#include "Appearance.h"
#include "ParticleModel.h"
#include "Transform.h"

#include <vector>

using namespace std;
using namespace DirectX;

class Particle
{
public:
	Particle();
	Particle(Geometry particleGeometry, ID3D11Device* device, const Vector3D startPosition);
	~Particle();

	Transform*     GetTransform()     const { return _transform; }
	Appearance*    GetAppearance()    const { return _appearance; }
	ParticleModel* GetParticleModel() const { return _particleModel; }
	float GetLifespan() const { return _lifespan; }
	Material GetMaterial() { return particleMaterial; }

	void SetLifespan(float newSpan) { _lifespan = newSpan; }

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);
private:
	Transform*     _transform;
	Appearance*    _appearance;
	ParticleModel* _particleModel;

	ID3D11ShaderResourceView* _pTexture = nullptr;
	ID3D11Buffer* _pBuffer;
	ConstantBuffer constBuff;

	float _lifespan = 2.5f;

	Material particleMaterial;
};

class ParticleSystem
{
public:
	ParticleSystem(int particleCount, Geometry particleGeometry, ID3D11DeviceContext* context, ID3D11Device* device, Vector3D position);
	~ParticleSystem();

	void Update(float t);
	void Draw();

	Vector3D SetEmissionPosition(Vector3D position) { _emissionPosition = position; }

	Particle* GetArray() { return _mParticles; }
private:
	Particle* _mParticles;
	Vector3D _emissionPosition;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	ID3D11Device* _pd3dDevice = nullptr;
};

