#include "Transform.h"

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale) 
{
    _position = position;
    _rotation = rotation;
    _scale = scale;
}

Transform::Transform() 
{

}

Transform::~Transform() 
{

}