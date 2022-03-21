#include "ParticleSystem.h"

#include "DDSTextureLoader.h"

// ------------------------------------------------------------

//Particle Class functions
Particle::Particle(Geometry particleGeometry, ID3D11Device* device, const Vector3D startPosition)
{
	Vector3D defaultVelocity     = { 0.0f, 0.0f, 0.0f };
	Vector3D defaultAcceleration = { 0.0f, 0.0f, 0.0f };
	float    defaultMass         = 0.001f;

	particleMaterial.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	particleMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	particleMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	particleMaterial.specularPower = 0.0f;

	_transform     = new Transform;
	_appearance    = new Appearance(particleGeometry, particleMaterial, "Particle");
	_particleModel = new ParticleModel(defaultVelocity, defaultAcceleration, defaultMass);

	_transform->SetPosition(startPosition);

	CreateDDSTextureFromFile(device, L"Resources\\stone.dds", nullptr, &_pTexture);

	_appearance->SetTextureRV(_pTexture);
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

	if (_pTexture != nullptr)
	{
		delete _pTexture;
		_pTexture = nullptr;
	}
}

void Particle::Update(float t)
{
	Vector3D lift;
	float x = (float)(rand() * 10.0f) - 5.0f;
	float y = (float)(rand() * 5.0f);
	float z = (float)(rand() * 10.0f) - 5.0f;

	lift.x = x;
	lift.y = y;
	lift.z = z;

	_particleModel->SetLift(lift);


	_particleModel->UpdateState(t);
	_transform->Update(t);
}

void Particle::Draw(ID3D11DeviceContext* pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}

// ----------------------------------------------------
//Particle System functions

ParticleSystem::ParticleSystem(int particleCount, Geometry particleGeometry, ID3D11DeviceContext* context, ID3D11Device* device, Vector3D position)
{
	_mParticles = new Particle[particleCount];

	for (int i = 0; i < particleCount; i++)
	{
		_mParticles[i] = Particle(particleGeometry, device, position);
	}

	_pImmediateContext = context;
	_pd3dDevice = device;
}

ParticleSystem::~ParticleSystem()
{
	delete[] _mParticles;
	_mParticles = nullptr;

	if(_pd3dDevice != nullptr)
	{
		delete _pd3dDevice;
		_pd3dDevice = nullptr;
	}

	if(_pImmediateContext != nullptr)
	{
		delete _pImmediateContext;
		_pImmediateContext = nullptr;
	}
}

void ParticleSystem::Update(float t)
{
	int currentParticles = sizeof(_mParticles) / sizeof(_mParticles[0]);
	for (int i = 0; i < currentParticles; i++)
	{
		if (_mParticles[i].GetLifespan() > 0.0f)
		{
			_mParticles[i].Update(t);
			_mParticles[i].SetLifespan(_mParticles[i].GetLifespan() - FPS_60);
		}
	}
}

void ParticleSystem::Draw()
{
	int currentParticles = sizeof(_mParticles) / sizeof(_mParticles[0]);

	for (int i = 0; i < currentParticles; i++)
	{
		if (_mParticles[i].GetLifespan() > 0.0f)
		{
			_mParticles[i].Draw(_pImmediateContext);
		}
	}
}
