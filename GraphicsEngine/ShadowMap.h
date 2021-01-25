#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

#include "Shader.h"

using namespace DirectX;

class OldShadowMap
{
public:
	OldShadowMap(ID3D11Device* device ,UINT width, UINT height);
	~OldShadowMap();

	ID3D11ShaderResourceView** DepthMapSRV();

	void BindDsvAndSetNullRenderTarget(ID3D11DeviceContext* dc);

private:
	OldShadowMap(const OldShadowMap& rhs);
	OldShadowMap& operator=(const OldShadowMap& rhs);

private:
	UINT mWidth;
	UINT mHeight;

	Shader* shaders;

	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;
	ID3D11RasterizerState* depthRas;

	D3D11_VIEWPORT mViewport;
};



