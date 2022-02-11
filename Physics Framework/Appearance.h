#pragma once

#include "Vector3D.h"
#include "Structures.h"

class Appearance
{
private:
	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView* _textureRV;

public:
	Appearance(Geometry geometry, Material material) { _geometry = geometry; _material = material; }
	~Appearance() { if (_textureRV) delete _textureRV; _textureRV = nullptr; }
	Geometry GetGeometryData() const { return _geometry; }
	Material GetMaterialData() const { return _material; }

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }
};

