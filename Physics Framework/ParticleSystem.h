#pragma once

#include <DirectXMath.h>
#include <d3d11_1.h>

#include "GameObject.h"

#include <vector>



using namespace std;
using namespace DirectX;

class ParticleSystem
{
public:
	ParticleSystem(int particleCount, Transform* transform, Appearance* appearance, ParticleModel* particleModel, const Vector3D position, ID3D11DeviceContext* device, ID3D11Device* device);
	~ParticleSystem();

	void Update(float t);
	void Draw();

	int GetParticleCount() { return _numOfParticles; }

	Vector3D SetEmissionPosition(Vector3D position) { _emissionPosition = position; }

	std::vector<GameObject*> GetArray() { return _mParticles; }
private:
	std::vector<GameObject*> _mParticles;
	Vector3D _emissionPosition;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;
	ID3D11Device* _pd3dDevice = nullptr;
	int _numOfParticles;
};

