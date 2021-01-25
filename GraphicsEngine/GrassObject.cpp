#include "GrassObject.h"
#include "Shader.h"
#include <d3dcompiler.h>

using namespace DirectX;

void GrassObject::GenerateGrass()
{

	float xRange = (abs(_minBounds.x) + abs(_maxBounds.x));
	float yRange = (abs(_minBounds.y) + abs(_maxBounds.y));
	float zRange = (abs(_minBounds.z) + abs(_maxBounds.z));

	float dX = xRange / _density;
	float dY = yRange / _density;
	float dZ = zRange / _density;;

	float x;
	float y;
	float z;


	for (int i = 0; i < _density+1; i++)
	{
		z = (dZ * i) + _minBounds.z;
		for (int j = 0; j < 1; j++)
		{
			y = (dY * j) + _minBounds.y;
			for (int k = 0; k < _density+1; k++)
			{
				x = (dX * k) + _minBounds.x;
////				CBPerGrass newGrass;
//				newGrass.GrassColor = XMFLOAT4(0.3, 1.0f, 0.1, 1.0f);
//				newGrass.GrassSize = XMFLOAT2(GrassWidth+ ((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4)))-2.0f) , GrassHeight + ((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 7))) - 2.5f));
//				newGrass.Position = XMFLOAT4(x + ((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / GrassWidth))) - (GrassWidth*0.5f)), y , z+ ((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / GrassWidth))) - (GrassWidth*0.5f)), 1);
				
//				GrassBlades.push_back(newGrass);
			}
		}
	}

	int i = 0;

	i++;
}

void GrassObject::Initialize(ID3D11Device * device)
{
	_device = device;
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(L"GrassGS.fx", nullptr, nullptr, "GS_GrassLowQuality", "gs_4_0",
		dwShaderFlags, 0, &GS_Buffer, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		if (pErrorBlob) pErrorBlob->Release();
	}

	if (pErrorBlob) pErrorBlob->Release();

	hr = _device->CreateGeometryShader(GS_Buffer->GetBufferPointer(), GS_Buffer->GetBufferSize(), NULL, &GS);




	D3D11_BUFFER_DESC bd;

	//// Create the constant buffer
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(CBBillboardFrame);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//hr = _device->CreateBuffer(&bd, nullptr, &_frameBuffer);

	//if (FAILED(hr))
	//	return;

	// Create the constant buffer


	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(CBPerGrass);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = _device->CreateBuffer(&bd, nullptr, &_grassBuffer);

	if (FAILED(hr))
		return;

	WORD indexData[1]{ 0 };

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 1;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexData;


	hr = _device->CreateBuffer(&bd, &InitData, &_indexBuffer);

	//D3D11_SAMPLER_DESC sdesc;
	//sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//sdesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	//sdesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	//sdesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	//sdesc.MipLODBias = 0;
	//sdesc.MaxAnisotropy = 1;
	//sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//sdesc.BorderColor[4] = { 0.0f };
	//sdesc.MinLOD = 0;
	//sdesc.MaxLOD = 0;

	//hr = _device->CreateSamplerState(&sdesc, &Sampler);
	//if (FAILED(hr))
	//	return;

	Vertex newVertex;
	newVertex.Pos = XMFLOAT3(0, 0, 0);
	newVertex.Normal = XMFLOAT4(1, 0, 0, 0);
	newVertex.Tangent = XMFLOAT3(0, 0, 1);
	newVertex.TexCoords = XMFLOAT2(0, 0);
	Vertex VertexData[1]{ newVertex };

	
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = VertexData;

	hr = _device->CreateBuffer(&bd, &InitData, &_vertexBuffer);



	ID3DBlob* pVSBlob = nullptr;
	ID3DBlob* pPSBlob = nullptr;

	shaders = new Shader(L"GrassGS.fx", "VS", "", "vs_4_0", "ps_4_0", device, &pVSBlob, NULL);

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.FrontCounterClockwise = true;
	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = _device->CreateRasterizerState(&cmdesc, &RSCullNone);

	if (FAILED(hr))
		return;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	20,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TANGENT",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	36,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		
		//Grass Instance
		{ "INSTANCEPOS",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 0,  D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{ "INSTANCECOLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{ "INSTANCESIZE", 0, DXGI_FORMAT_R32G32_FLOAT,			1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},

	};

	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &_pVertexLayout);

	GenerateGrass();

	// Create our trees instance buffer
// Pretty much the same thing as a regular vertex buffer, except that this buffers data
// will be used per "instance" instead of per "vertex". Each instance of the geometry
// gets it's own instanceData data, similar to how each vertex of the geometry gets its own
// Vertex data
	D3D11_BUFFER_DESC instBuffDesc;
	ZeroMemory(&instBuffDesc, sizeof(instBuffDesc));

	instBuffDesc.Usage = D3D11_USAGE_DEFAULT;
///	instBuffDesc.ByteWidth = sizeof(CBPerGrass) * GrassBlades.size();
	instBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instBuffDesc.CPUAccessFlags = 0;
	instBuffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA instData;
	ZeroMemory(&instData, sizeof(instData));

//	instData.pSysMem = &GrassBlades[0];
	hr = device->CreateBuffer(&instBuffDesc, &instData, &_grassInstance);

}

void GrassObject::Update(float deltaTime)
{
}

void GrassObject::Draw(ID3D11DeviceContext *& Context, UINT * stride, UINT * offset, ID3D11Buffer * Buffer)
{
	LoadGS(Context);

	//Context->VSSetConstantBuffers(2, 1, &_frameBuffer);
	//Context->VSSetConstantBuffers(3, 1, &_billboardBuffer);
	Context->VSSetConstantBuffers(1, 1, &Buffer);

	ID3D11Buffer* tempBuffer;
	Context->VSGetConstantBuffers(0, 1, &tempBuffer);

	Context->GSSetConstantBuffers(0, 1, &tempBuffer);
	Context->GSSetConstantBuffers(1, 1, &Buffer);
	Context->GSSetConstantBuffers(2, 1, &_grassBuffer);


	Context->PSSetConstantBuffers(0, 1, &tempBuffer);
	Context->PSSetConstantBuffers(1, 1, &Buffer);


	//Context->UpdateSubresource(_frameBuffer, 0, nullptr, &_cbFrameBuffer, 0, 0);
	Context->IASetIndexBuffer(*&_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	Context->IASetVertexBuffers(0, 1, &_vertexBuffer, *&stride, *&offset);
	Context->IASetVertexBuffers(1, 1, &_grassInstance, *&stride, *&offset);


//	ObjectConstantBuffer.hasTextureMap = 0.0f;


//	ObjectConstantBuffer.mWorld = GetWorldMatrix();
//	Context->UpdateSubresource(Buffer, 0, nullptr, &ObjectConstantBuffer, 0, 0);

//	Context->UpdateSubresource(_grassBuffer, 0, nullptr, &GrassBlades[0], 0, 0);
//	Context->GSSetConstantBuffers(2, 1, &_grassBuffer);

//	Context->DrawInstanced(1,GrassBlades.size(), 0, 0);


	UnloadGS(Context);

}

void GrassObject::LoadGS(ID3D11DeviceContext *& Context)
{
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	Context->IASetInputLayout(_pVertexLayout);

	//Context->RSSetState(RSCullNone);

	Context->VSSetShader(shaders->GetVS(), 0, 0);
	Context->GSSetShader(GS, 0, 0);
}

void GrassObject::UnloadGS(ID3D11DeviceContext *& Context)
{

	Context->GSSetShader(0, 0, 0);
	//Context->VSSetShader(0, 0, 0);
	Context->IASetInputLayout(_pVertexLayout);

	//Context->RSSetState(0);

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

GrassObject::GrassObject() : SceneObject("Grass"), IDrawable(false)
{
}


GrassObject::~GrassObject()
{
}
