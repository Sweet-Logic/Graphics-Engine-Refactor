#include "BillboardObject.h"
#include "Texture2D.h"
#include <d3dcompiler.h>

using namespace DirectX;


BillboardObject* BillboardObject::instance = nullptr;


BillboardObject::BillboardObject() : SceneObject("BillBoard"), IDrawable(false)
{
}


BillboardObject::~BillboardObject()
{
}

void BillboardObject::Initialize(ID3D11Device * device)
{
//	_device = device;
//	HRESULT hr = S_OK;
//
//	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined(DEBUG) || defined(_DEBUG)
//	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//	// Setting this flag improves the shader debugging experience, but still allows 
//	// the shaders to be optimized and to run exactly the way they will run in 
//	// the release configuration of this program.
//	dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
//
//	ID3DBlob* pErrorBlob;
//	hr = D3DCompileFromFile(L"BillboardGS.fx", nullptr, nullptr, "GS_Billboard", "gs_4_0",
//		dwShaderFlags, 0, &GS_Buffer, &pErrorBlob);
//
//	if (FAILED(hr))
//	{
//		if (pErrorBlob != nullptr)
//			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
//
//		if (pErrorBlob) pErrorBlob->Release();
//	}
//
//	if (pErrorBlob) pErrorBlob->Release();
//
//	hr = _device->CreateGeometryShader(GS_Buffer->GetBufferPointer(), GS_Buffer->GetBufferSize(), NULL, &GS);
//
//
//
//
//	D3D11_BUFFER_DESC bd;
//
//	// Create the constant buffer
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(CBBillboardFrame);
//	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	bd.CPUAccessFlags = 0;
//	hr = _device->CreateBuffer(&bd, nullptr, &_frameBuffer);
//
//	if (FAILED(hr))
//		return;
//
//	// Create the constant buffer
//
//
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(CBPerBillboard);
//	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	bd.CPUAccessFlags = 0;
//	hr = _device->CreateBuffer(&bd, nullptr, &_billboardBuffer);
//
//	if (FAILED(hr))
//		return;
//
//	WORD indexData[1]{ 0 };
//
//	ZeroMemory(&bd, sizeof(bd));
//
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(WORD) * 1;
//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	D3D11_SUBRESOURCE_DATA InitData;
//
//	ZeroMemory(&InitData, sizeof(InitData));
//	InitData.pSysMem = indexData;
//
//
//	hr = _device->CreateBuffer(&bd, &InitData, &_indexBuffer);
//
//	//D3D11_SAMPLER_DESC sdesc;
//	//sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//	//sdesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
//	//sdesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
//	//sdesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
//	//sdesc.MipLODBias = 0;
//	//sdesc.MaxAnisotropy = 1;
//	//sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//	//sdesc.BorderColor[4] = { 0.0f };
//	//sdesc.MinLOD = 0;
//	//sdesc.MaxLOD = 0;
//
//	//hr = _device->CreateSamplerState(&sdesc, &Sampler);
//	//if (FAILED(hr))
//	//	return;
//
//	D3D11_RASTERIZER_DESC cmdesc;
//	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
//	cmdesc.FillMode = D3D11_FILL_SOLID;
//	cmdesc.FrontCounterClockwise = true;
//	cmdesc.CullMode = D3D11_CULL_NONE;
//	hr = _device->CreateRasterizerState(&cmdesc, &RSCullNone);
//
//	if (FAILED(hr))
//		return;
//
//	ObjectConstantBuffer.clipTexture = 1.0f;

}

void BillboardObject::Update(float deltaTime)
{
}

void BillboardObject::Draw(ID3D11DeviceContext *& Context, UINT * stride, UINT * offset, ID3D11Buffer * Buffer)
{
	//LoadGS(Context);
	//Context->VSSetConstantBuffers(1, 1, &Buffer);
	////Context->VSSetConstantBuffers(2, 1, &_frameBuffer);
	////Context->VSSetConstantBuffers(3, 1, &_billboardBuffer);

	//ID3D11Buffer* tempBuffer;
	//Context->VSGetConstantBuffers(0, 1, &tempBuffer);

	//Context->GSSetConstantBuffers(0, 1, &tempBuffer);
	//Context->GSSetConstantBuffers(1, 1, &Buffer);
	//Context->GSSetConstantBuffers(2, 1, &_frameBuffer);
	//Context->GSSetConstantBuffers(3, 1, &_billboardBuffer);


	//Context->PSSetConstantBuffers(0, 1, &tempBuffer);
	//Context->PSSetConstantBuffers(1, 1, &Buffer);
	//Context->PSSetConstantBuffers(2, 1, &_frameBuffer);
	//Context->PSSetConstantBuffers(3, 1, &_billboardBuffer);

	//Context->UpdateSubresource(_frameBuffer, 0, nullptr, &_cbFrameBuffer, 0, 0);
	//Context->IASetIndexBuffer(*&_indexBuffer, DXGI_FORMAT_R16_UINT, 0);



	//for (int i = 0; i < billboards.size(); i++)
	//{
	//	Context->IASetVertexBuffers(0, 1, &billboards[i]._vertexBuffer, *&stride, *&offset);
	//	billboards[i]._cbBillboardBuffer.BillboardImageHeight = billboards[i].Texture->GetHeight();
	//	billboards[i]._cbBillboardBuffer.BillboardImageWidth = billboards[i].Texture->GetWidth();

	//	ObjectConstantBuffer.mWorld = XMMatrixTranspose(GetWorldMatrix() + XMMatrixTranslation(billboards[i].Position.x, billboards[i].Position.y, billboards[i].Position.z));
	//	Context->UpdateSubresource(Buffer, 0, nullptr, &ObjectConstantBuffer, 0, 0);
	//	Context->VSGetConstantBuffers(1, 1, &Buffer);

	//	Context->UpdateSubresource(_billboardBuffer, 0, nullptr, &billboards[i]._cbBillboardBuffer, 0, 0);


	//	Context->PSSetShaderResources(1, 1, billboards[i].Texture->GetTexture());

	//	Context->DrawIndexed(1, 0, 0);
	//}


	//

	//UnloadGS(Context);
}

void BillboardObject::LoadGS(ID3D11DeviceContext *& Context)
{

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	Context->GSSetShader(GS, 0, 0);

	//Context->PSSetSamplers(0, 1, &Sampler);
	//Context->RSSetState(RSCullNone);



}

void BillboardObject::UnloadGS(ID3D11DeviceContext *& Context)
{

	Context->GSSetShader(0, 0, 0);

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//Context->PSSetShader(0, 0, 0);

	//Context->RSSetState(nullptr);

}

void BillboardObject::AddBillboard(XMFLOAT3 position, Texture2D* texture)
{
	/*BillboardData newBillboard;

	Vertex newVertex;
	newVertex.Pos = XMFLOAT3(0, 0, 0);
	newVertex.Normal = XMFLOAT4(0, 0, 0, 0);
	newVertex.Tangent = XMFLOAT3(0, 0, 0);
	newVertex.TexCoords = XMFLOAT2(0, 0);
	Vertex VertexData[1]{ newVertex };

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = VertexData;

	HRESULT hr = _device->CreateBuffer(&bd, &InitData,&newBillboard._vertexBuffer);

	newBillboard.Texture = texture;
	newBillboard.Position = position;
	newBillboard._cbBillboardBuffer.Position = XMFLOAT4(position.x, position.y, position.z, 1.0f);
	newBillboard.Texture->Initialize();
	billboards.push_back(newBillboard);*/
}
