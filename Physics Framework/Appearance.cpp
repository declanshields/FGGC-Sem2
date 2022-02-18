#include "Appearance.h"

Appearance::Appearance(Geometry geometry, Material material, std::string type)
{ 
	_geometry = geometry; 
	_material = material; 
	_type = type; 
}

Appearance::Appearance()
{

}

void Appearance::Draw(ID3D11DeviceContext* pImmediateContext)
{
	ID3D11Buffer* const vBuff = GetGeometryData().vertexBuffer;
	UINT const vStride = GetGeometryData().vertexBufferStride;
	UINT const vOffset = GetGeometryData().vertexBufferOffset;;
	ID3D11Buffer* iBuff = GetGeometryData().indexBuffer;
	UINT const iNum = GetGeometryData().numberOfIndices;

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &vBuff, &vStride, &vOffset);
	pImmediateContext->IASetIndexBuffer(iBuff, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(iNum, 0, 0);
}

Appearance::~Appearance()
{
	if (_textureRV) 
	{
		delete _textureRV;
		_textureRV = nullptr;
	}
}