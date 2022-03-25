#pragma once

#include "Vector3D.h"
#include "Structures.h"
#include <string>

class Appearance
{
private:
	Geometry _geometry;
	Material _material;
	std::string _type;

	ID3D11ShaderResourceView* _textureRV = nullptr;

public:
	Appearance(Geometry geometry, Material material, std::string type);
	Appearance();
	~Appearance();

	Geometry GetGeometryData() const { return _geometry; }
	Material GetMaterialData() const { return _material; }
	std::string GetType() const { return _type; }

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void Draw(ID3D11DeviceContext* pImmediateContext);
};

