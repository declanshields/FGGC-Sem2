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
	Particle(Geometry particleGeometry);
	~Particle();

	Transform*     GetTransform()     const { return _transform; }
	Appearance*    GetAppearance()    const { return _appearance; }
	ParticleModel* GetParticleModel() const { return _particleModel; } 

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

	float GetLifespan() const { return _lifespan; }
private:
	Transform*     _transform;
	Appearance*    _appearance;
	ParticleModel* _particleModel;

	float _lifespan = 2.5f;

	Material particleMaterial;
};

class ParticleSystem
{
public:
	ParticleSystem(int particleCount, Geometry particleGeometry);
	~ParticleSystem();

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateDevice);

	Vector3D SetEmissionPosition(Vector3D position) { _emissionPosition = position; }
private:
	Particle* _mParticles;
	Vector3D _emissionPosition;
};

