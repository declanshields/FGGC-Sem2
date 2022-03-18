#include "ParticleSystem.h"

// ------------------------------------------------------------

//Particle Class functions
Particle::Particle(Geometry particleGeometry)
{
	Vector3D defaultVelocity     = { 0.0f, 0.0f, 0.0f };
	Vector3D defaultAcceleration = { 0.0f, 0.0f, 0.0f };
	float    defaultMass         = 0.001f;

	particleMaterial.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	particleMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	particleMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	particleMaterial.specularPower = 0.0f;

	_transform     = new Transform;
	_appearance    = new Appearance();
	_particleModel = new ParticleModel(defaultVelocity, defaultAcceleration, defaultMass);
}

Particle::Particle()
{

}

Particle::~Particle()
{
	delete _transform;
	_transform = nullptr;

	delete _appearance;
	_appearance = nullptr;

	delete _particleModel;
	_particleModel = nullptr;
}

void Particle::Update(float t)
{



	_particleModel->UpdateState(t);
	_transform->Update(t);
}

void Particle::Draw(ID3D11DeviceContext* pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}

// ----------------------------------------------------
//Particle System functions

ParticleSystem::ParticleSystem(int particleCount, Geometry particleGeometry)
{
	_mParticles = new Particle[particleCount];

	for (int i = 0; i < particleCount; i++)
	{
		_mParticles[i] = Particle(particleGeometry);
	}
}

ParticleSystem::~ParticleSystem()
{
	delete[] _mParticles;
	_mParticles = nullptr;
}

void ParticleSystem::Update(float t)
{
	int currentParticles = sizeof(_mParticles) / sizeof(_mParticles[0]);
	for (int i = 0; i < currentParticles; i++)
	{
		if (_mParticles[i].GetLifespan() > 0.0f) 
		{
			_mParticles[i].Update(t);
		}
	}
}

void ParticleSystem::Draw(ID3D11DeviceContext* pImmediateContext)
{
	int currentParticles = sizeof(_mParticles) / sizeof(_mParticles[0]);

	for (int i = 0; i < currentParticles; i++)
	{
		if (_mParticles[i].GetLifespan() > 0.0f)
		{
			_mParticles[i].Draw(pImmediateContext);
		}
	}
}
