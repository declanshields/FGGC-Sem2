#include "ParticleSystem.h"

#include "DDSTextureLoader.h"

// ----------------------------------------------------
//Particle System functions

ParticleSystem::ParticleSystem(int particleCount, Transform* transform, Appearance* appearance, ParticleModel* particleModel, const Vector3D position, ID3D11DeviceContext* context, ID3D11Device* device)
{
	_pImmediateContext = context;

	CreateDDSTextureFromFile(device, L"Resources\\stone.dds", nullptr, &texture);

	for (int i = 0; i < particleCount; i++)
	{
		_mParticles.push_back(new GameObject(transform, appearance, particleModel, position));
		_mParticles[i]->GetAppearance()->SetTextureRV(texture);
	}

	_numOfParticles = particleCount;
}



ParticleSystem::~ParticleSystem()
{
	_mParticles.clear();

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

	texture->Release();
}

void ParticleSystem::Update(float t)
{
	
	for (int i = 0; i < _numOfParticles; i++)
	{
		if (_mParticles[i]->GetLifespan() > 0.0f)
		{
			_mParticles[i]->Update(t);
			_mParticles[i]->SetLifespan(_mParticles[i]->GetLifespan() - FPS_60);
		}
	}
}

void ParticleSystem::Draw()
{
	for (int i = 0; i < _numOfParticles; i++)
	{
		if (_mParticles[i]->GetLifespan() > 0.0f)
		{
			_mParticles[i]->Draw(_pImmediateContext);
		}
	}
}
