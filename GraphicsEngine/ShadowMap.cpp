#include "ShadowMap.h"




OldShadowMap::OldShadowMap(ID3D11Device * device, UINT width, UINT height) : mWidth(width), mHeight(height), mDepthMapDSV(0), mDepthMapSRV(0)
{
	// Viewport that matches the shadow mao dimentions.
	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
	mViewport.Width = static_cast<float>(width);
	mViewport.Height = static_cast<float>(height);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

	D3D11_TEXTURE2D_DESC texDec;
	texDec.Width = mWidth;
	texDec.Height = mHeight;
	texDec.MipLevels = 1;
	texDec.ArraySize = 1;
	texDec.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDec.SampleDesc.Count = 1;
	texDec.SampleDesc.Quality = 0;
	texDec.Usage = D3D11_USAGE_DEFAULT;
	texDec.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDec.CPUAccessFlags = 0;
	texDec.MiscFlags = 0;

	ID3D11Texture2D* depthMap = 0;
	HRESULT hr = device->CreateTexture2D(&texDec, 0, &depthMap);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	
	hr = device->CreateDepthStencilView(depthMap,&dsvDesc, &mDepthMapDSV);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDec.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	hr = device->CreateShaderResourceView(depthMap, &srvDesc, &mDepthMapSRV);

	depthMap->Release();

	ID3DBlob* pVSBlob = nullptr;
	ID3DBlob* pPSBlob = nullptr;
	shaders = new Shader(L"ShadowMapping.fx", "VS", "PS", "vs_4_0", "ps_4_0", device, &pVSBlob, &pPSBlob);

	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.CullMode = D3D11_CULL_NONE;
	wfdesc.FillMode = D3D11_FILL_SOLID;
	wfdesc.DepthBias = 6000;
	wfdesc.DepthBiasClamp = 0.0f;
	wfdesc.SlopeScaledDepthBias = 1.0f;
	hr = device->CreateRasterizerState(&wfdesc, &depthRas);

}

OldShadowMap::~OldShadowMap()
{
}

ID3D11ShaderResourceView ** OldShadowMap::DepthMapSRV()
{
	return &mDepthMapSRV;
}

void OldShadowMap::BindDsvAndSetNullRenderTarget(ID3D11DeviceContext * dc)
{

	dc->RSSetViewports(1, &mViewport);
	dc->VSSetShader(shaders->GetVS(), nullptr, 0);
	dc->PSSetShader(shaders->GetPS(), nullptr, 0);
	
	ID3D11RenderTargetView* renderTargets[1] = { NULL };
	dc->OMSetRenderTargets(1, renderTargets, mDepthMapDSV);
	dc->ClearDepthStencilView(mDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	dc->RSSetState(depthRas);
}

OldShadowMap::OldShadowMap(const OldShadowMap & rhs)
{
}

OldShadowMap & OldShadowMap::operator=(const OldShadowMap & rhs)
{
	// TODO: insert return statement here
	//this->mDepthMapDSV = rhs.mDepthMapDSV;
	return *this;
}
