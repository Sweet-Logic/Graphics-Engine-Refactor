#include "SkyMapObject.h"
#include "MeshComponent.h"
#include "DDSTextureLoader.h"
#include "Shader.h"
#include "Application.h"



SkyMapObject::SkyMapObject(std::string _objectName) : CubeObject(_objectName)
{
}


SkyMapObject::~SkyMapObject()
{
}

void SkyMapObject::Initialize(ID3D11Device* _pd3dDevice)
{
	CubeObject::Initialize(_pd3dDevice);

	SKYMAP = new Shader(L"skyMap.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &SKYMAP_VS_Buffer, &SKYMAP_PS_Buffer);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	_pd3dDevice->CreateDepthStencilState(&dssDesc, &DSLessEqual);

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.FrontCounterClockwise = true;
	cmdesc.CullMode = D3D11_CULL_NONE;
	HRESULT hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &RSCullNone);

	hr = CreateDDSTextureFromFile(_pd3dDevice, L"maps/skymap.dds", (ID3D11Resource**)&SMTexture, &_skyTexview);


	/*D3D11_TEXTURE2D_DESC SMTextureDesc;
	SMTexture->GetDesc(&SMTextureDesc);
	SMTextureDesc.MiscFlags = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = _pd3dDevice->CreateShaderResourceView(SMTexture, &SMViewDesc, &_skyTexview);*/

	D3D11_SAMPLER_DESC sdesc;
	sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sdesc.MipLODBias = 0;
	sdesc.MaxAnisotropy = 1;
	sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sdesc.BorderColor[4] = { 0.0f };
	sdesc.MinLOD = 0;
	sdesc.MaxLOD = 0;

	hr = _pd3dDevice->CreateSamplerState(&sdesc, &Sampler);

	ScaleObject(XMVectorSet(10000.0f, 6000.0f, 10000.0f, 1.0f));

	TranslateObject(XMVectorSet(0.0f, 10.0f, 0.0f, 1.0f));

}


void SkyMapObject::Update(float deltaTime)
{
	/*CubeObject::Update(deltaTime);
	XMFLOAT3 cameraPosition;

	if (Application::_currentCamera == nullptr)
	{
		cameraPosition = XMFLOAT3(0, 0, 0);
	}
	else
	{
		XMStoreFloat3(&cameraPosition, Application::_currentCamera->GetWorldPosition());
	}

	TranslateObject(XMVectorSet(cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f));*/

}

void SkyMapObject::StartDraw(ID3D11DeviceContext *& Context)
{
	Context->OMSetBlendState(nullptr, nullptr, 0xffffffff);

	Context->VSSetShader(SKYMAP->GetVS(), 0, 0);
	Context->PSSetShader(SKYMAP->GetPS(), 0, 0);
	Context->PSSetSamplers(0, 1, &Sampler);


	Context->OMSetDepthStencilState(DSLessEqual, 0);
	Context->RSSetState(RSCullNone);

}

void SkyMapObject::Draw(ID3D11DeviceContext *& Context, UINT * stride, UINT * offset, ID3D11Buffer * Buffer)
{
	StartDraw(Context);
	Context->PSSetShaderResources(Map::rDiffuse, 1, &_skyTexview);

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer, true);

	EndDraw(Context);
}

void SkyMapObject::EndDraw(ID3D11DeviceContext *& Context)
{
	Context->OMSetDepthStencilState(NULL, 0);
	Context->RSSetState(nullptr);

	Context->PSSetShaderResources(Map::rDiffuse, 1, pSRV);
}
