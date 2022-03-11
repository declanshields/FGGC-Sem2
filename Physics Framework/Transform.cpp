#include "Transform.h"

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale) 
{
    _position = position;
    _rotation = rotation;
    _scale = scale;
}

Transform::Transform() 
{
    _position = Vector3D();
    _rotation = Vector3D();
    _scale = Vector3D();
}

void Transform::Update(float t)
{
    //Calculate world matrix
    XMMATRIX scale = XMMatrixScaling(GetScale().x, GetScale().y, GetScale().z);
    XMMATRIX rotation = XMMatrixRotationX(GetRotation().x) * XMMatrixRotationY(GetRotation().y) * XMMatrixRotationZ(GetRotation().z);
    XMMATRIX translation = XMMatrixTranslation(GetPosition().x, GetPosition().y, GetPosition().z);

    SetWorldMatrix(scale * rotation * translation);

    if (_parent != nullptr) 
    {
        SetWorldMatrix(GetWorldMatrix() * _parent->GetWorldMatrix());
    }
}

Transform::~Transform() 
{
    if (_parent) 
    {
        delete _parent;
        _parent = nullptr;
    }
}

void Transform::SetScale(Vector3D scale)
{
    _scale = scale;

    _centerOfMass.x *= _scale.x;
    _centerOfMass.y *= _scale.y;
    _centerOfMass.z *= _scale.z;
}