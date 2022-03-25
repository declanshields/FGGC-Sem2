#include "GameObject.h"

GameObject::GameObject(Transform* transform, Appearance* appearance, ParticleModel* particleModel)
{
	_transform = transform;

	_appearance = appearance;

	_particleModel = particleModel;

	if (_appearance->GetType() == "Cube")
		Debug::DebugMsg("This object is a cube");
}

GameObject::GameObject(Transform* transform, Appearance* appearance, ParticleModel* particleModel, const Vector3D startPosition)
{
	Vector3D defaultVelocity = { 0.0f, 0.0f, 0.0f };
	Vector3D defaultAcceleration = { 0.0f, 0.0f, 0.0f };
	float    defaultMass = 0.001f;

	_transform = transform;
	_appearance = appearance;
	_particleModel = particleModel;

	_particleModel->SetMass(defaultMass);
	_particleModel->SetVelocity(defaultVelocity);
	_particleModel->SetAcceleration(defaultAcceleration);

	_transform->SetPosition(startPosition);
}

GameObject::~GameObject()
{
	delete _transform;
	_transform = nullptr;

	delete _particleModel;
	_particleModel = nullptr;

	delete _appearance;
	_appearance = nullptr;
}

void GameObject::Update(float t)
{
	//if(_appearance->GetType() == "Particle")
	//	_particleModel->UpdateState(t);
	//else
	//	_transform->Update(t);

	_transform->Update(t);
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place
	_appearance->Draw(pImmediateContext);
}
