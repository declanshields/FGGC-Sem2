#include "ParticleSystem.h"

#include "DDSTextureLoader.h"

// ----------------------------------------------------
//Particle System functions

ParticleSystem::ParticleSystem(int particleCount, Geometry geometry, Material material, const Vector3D position, ID3D11DeviceContext* context, ID3D11Device* device)
{
	_pImmediateContext = context;
	_pd3dDevice = device;

	_mParticles.reserve(particleCount);

	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\stone.dds", nullptr, &texture);

	for (int i = 0; i < particleCount; i++)
	{
		GameObject* gameObject = new GameObject(new Transform(), new Appearance(geometry, material, "Particle"), new ParticleModel(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f), position);
		gameObject->GetParticleModel()->SetObject(gameObject);
		gameObject->GetTransform()->SetScale(Vector3D(0.1f, 0.1f, 0.1f));
		gameObject->GetTransform()->SetPosition(position);
		gameObject->GetParticleModel()->SetMass(1.0f);
		gameObject->GetParticleModel()->SetAcceleration(Vector3D(0.0f, 0.0f, 0.0f));
		gameObject->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
		gameObject->GetAppearance()->SetTextureRV(texture);
		gameObject->SetLifespan(rand() % 3);

		_mParticles.push_back(gameObject);
	}

	_numOfParticles = particleCount;
}

ParticleSystem::ParticleSystem()
{

}


ParticleSystem::~ParticleSystem()
{
	_mParticles.clear();
	texture->Release();
	texture = NULL;

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
	
	for (int i = 0; i < _numOfParticles; i++)
	{
		if (_mParticles[i]->GetLifespan() > 0.0f)
		{
			Vector3D lift = Vector3D();

			lift.x = ((((float)rand() / (float)RAND_MAX) * 1.5f) - 1.00f);
			lift.y = ((float)rand() / (float)RAND_MAX) * 5.0f - 1.0f;
			lift.z = ((((float)rand() / (float)RAND_MAX) * 1.5f) - 1.00f);

			_mParticles[i]->GetParticleModel()->SetVelocity(lift);
			_mParticles[i]->GetParticleModel()->MoveConstVelocity(t);

			Debug::DebugMsg(lift);

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
