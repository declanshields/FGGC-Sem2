#include "GameObject.h"

GameObject::GameObject(string type, Transform* transform, Appearance* appearance) : _type(type)
{
	_parent = nullptr;

	_transform = transform;

	_appearance = appearance;

	_textureRV = nullptr;

	Debug debugger = Debug();

	if (type == "Cube")
		debugger.DebugMsg("This object is a cube");
}

GameObject::~GameObject()
{
	delete _transform;
	_transform = nullptr;

	delete _textureRV;
	_textureRV = nullptr;

	delete _parent;
	_parent = nullptr;
}

void GameObject::Update(float t)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	_transform->SetWorldMatrix(scale * rotation * translation);

	if (_parent != nullptr)
	{
		_transform->SetWorldMatrix(_transform->GetWorldMatrix() * _parent->_transform->GetWorldMatrix());
	}

	Debug debugger = Debug();
	debugger.DebugMsg(std::to_string(t));
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	ID3D11Buffer* const vbuff = _appearance->GetGeometryData().vertexBuffer;
	UINT const vStride = _appearance->GetGeometryData().vertexBufferStride;


	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &vbuff, &vStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
