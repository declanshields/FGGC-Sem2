#include "Transform.h"

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale) 
{
    _position = position;
    _rotation = rotation;
    _scale = scale;

    _crossSectionalArea = (2*scale.x) * (2*scale.y);
}

Transform::Transform() 
{
    _position = Vector3D();
    _rotation = Vector3D();
    _scale = Vector3D();
    _angularVelocity = Vector3D();
    _angularAcceleration = Vector3D();
}

void Transform::Update(float t)
{    
    //Calculate angular velocity
    _angularVelocity = _angularVelocity + _angularAcceleration * t;
    
    //Calculate world matrix
    XMMATRIX scale = XMMatrixScaling(GetScale().x, GetScale().y, GetScale().z);
    XMMATRIX rotation = XMMatrixRotationX(GetRotation().x) * XMMatrixRotationY(GetRotation().y) * XMMatrixRotationZ(GetRotation().z);
    XMMATRIX translation = XMMatrixTranslation(GetPosition().x, GetPosition().y, GetPosition().z);

    if (!_fixed)
    {
        //Update Quaternion rotation
        Quaternion temp = { 0.0f, _angularVelocity.x, _angularVelocity.y, _angularVelocity.z };
        temp *= _qRotation;
        temp = temp * (t / 2);

        _qRotation = _qRotation + temp;

        XMMATRIX Quaternion = XMMatrixRotationX(_qRotation.i) * XMMatrixRotationY(_qRotation.j) * XMMatrixRotationZ(_qRotation.k);
        SetWorldMatrix(scale * Quaternion * translation);
    }
    else
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

    _crossSectionalArea = (2 * scale.x) * (2 * scale.y);
}