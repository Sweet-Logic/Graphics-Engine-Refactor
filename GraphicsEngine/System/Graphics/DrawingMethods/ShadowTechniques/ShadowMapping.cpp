#include "ShadowMapping.h"
#include "../../Graphics.h"
#include "../../ShaderManager.h"
#include "../../../../Resource/Textures/Texture2DFactory.h"
#include "../../Views/RenderTargetViews/RenderTargetView.h"
#include "../../Views/ShaderResourceViews/ShaderResourceView.h"
#include "../../VertexLayouts/BaseVertex.h"
#include "../../../../Object/Components/Renderer/RendererComponent.h"
#include "../../Shader.h"
#include "../../VertexLayouts/BaseVertex.h"

void ShadowMap::Initialise()
{
    Graphics* graphics = &Graphics::GetInstance();
    m_pImmediateContext = graphics->GetContext();
    m_pDevice = graphics->GetDevice();

	m_shaderManager = &ShaderManager::GetInstance();

	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
	mViewport.Width = static_cast<float>(m_width);
	mViewport.Height = static_cast<float>(m_height);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

	D3D11_TEXTURE2D_DESC texDec;
	texDec.Width = m_width;
	texDec.Height = m_height;
	texDec.MipLevels = 1;
	texDec.ArraySize = 1;
	texDec.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDec.SampleDesc.Count = 1;
	texDec.SampleDesc.Quality = 0;
	texDec.Usage = D3D11_USAGE_DEFAULT;
	texDec.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDec.CPUAccessFlags = 0;
	texDec.MiscFlags = 0;
	
	ID3D11Texture2D* depthMap = nullptr;

	ID3D11Device * device =  Graphics::GetInstance().GetDevice();

	HRESULT hr = device->CreateTexture2D(&texDec, nullptr, &depthMap);
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	
	hr = device->CreateDepthStencilView(depthMap,&dsvDesc, &m_depthMapDSV);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDec.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	hr = device->CreateShaderResourceView(depthMap, &srvDesc, &m_depthMapSRV);

	depthMap->Release();

	Shader* shaderArray[2] = 
	{
		nullptr,
		nullptr
	};
	ShaderManager::GetInstance().LoadShaders(shaderArray, 2, L"ShadowMapping.fx",(ShaderType)(E_VERTEX | E_PIXEL));
	m_pVertexShader = (VertexShader*)shaderArray[0];
	m_pPixelShader = (PixelShader*)shaderArray[1];

	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.CullMode = D3D11_CULL_NONE;
	wfdesc.FillMode = D3D11_FILL_SOLID;
	wfdesc.DepthBias = 6000;
	wfdesc.DepthBiasClamp = 0.0f;
	wfdesc.SlopeScaledDepthBias = 1.0f;
	hr = device->CreateRasterizerState(&wfdesc, &m_depthRas);

	//Create constant Buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MainConstants::Frame);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = m_pDevice->CreateBuffer(&bd, nullptr, &m_perFrameBuffer);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MainConstants::Object);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = m_pDevice->CreateBuffer(&bd, nullptr, &m_perObjectBuffer);
}

void ShadowMap::Release()
{
	m_depthMapSRV->Release();
	m_depthMapDSV->Release();
	m_depthRas->Release();
	m_pVertexShader->m_DX11Shader->Release();
	m_pPixelShader->m_DX11Shader->Release();
}

void ShadowMap::BuildShadowTransform(Lighting* currentLight, XMFLOAT4X4& view, XMFLOAT4X4& proj, XMFLOAT4X4& transform)
{
	if (currentLight != nullptr)
	{
		XMMATRIX V = XMMatrixIdentity();
		XMVECTOR targetPos = XMLoadFloat3(new XMFLOAT3(0.0f, 0.0f, 0.0f));
		switch (currentLight->lightType)
		{
		case E_POINT:
			break;
		case E_DIRECTIONAL:
			XMVECTOR lightDirection = XMLoadFloat3(&currentLight->Direction);
			XMVECTOR lightPosition = 1000.0f*lightDirection;
			XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

			V = XMMatrixLookAtLH(lightPosition, targetPos, up);
			break;
		case E_SPOT:
			break;
		default:
			break;
		}


		//Transform bounding sphere to light space
		XMFLOAT3 sphereCenterLS;
		XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

		//Ortho frustum in light space encloses scene
		float l = sphereCenterLS.x - 1000.0f;
		float b = sphereCenterLS.y - 1000.0f;
		float n = sphereCenterLS.z - 1000.0f;

		float r = sphereCenterLS.x + 1000.0f;
		float t = sphereCenterLS.y + 1000.0f;
		float f = sphereCenterLS.z + 1000.0f;

		XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

		//Transform NDC space [-1,+1]^2 to texture space [0,1]^2
		XMMATRIX T(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f);

		XMMATRIX S = V * P *T;

		XMStoreFloat4x4(&view, V);
		XMStoreFloat4x4(&proj, P);
		XMStoreFloat4x4(&transform, S);
	}
}


void ShadowMap::SetUp()
{
	m_pImmediateContext->RSSetViewports(1, &mViewport);
	m_shaderManager->BindShader(m_pVertexShader);
	m_shaderManager->BindShader(m_pPixelShader);
	
	//Ensures we dont write to screen and only the depth stencil
	m_pImmediateContext->ClearDepthStencilView(m_depthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pImmediateContext->OMSetRenderTargets(1, m_emptyView, m_depthMapDSV);
	m_pImmediateContext->RSSetState(m_depthRas);

	XMFLOAT4X4 view, proj, transform;
	BuildShadowTransform(m_shadowSource, view, proj, transform);
	XMMATRIX LightProj = XMLoadFloat4x4(&proj);
	XMMATRIX LightView = XMLoadFloat4x4(&view);
	//
	m_frameCB.View = XMMatrixTranspose(LightView);
	m_frameCB.Projection = XMMatrixTranspose(LightProj);
	m_frameCB.gCameraView = XMMatrixTranspose(LightView);
	m_frameCB.gCameraProj = XMMatrixTranspose(LightProj);

	m_pImmediateContext->UpdateSubresource(m_perFrameBuffer, 0, nullptr, &m_frameCB, 0, 0);
	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SHADOWN_MAP] = nullptr;

}

void ShadowMap::Execute()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	for (int i = 0; i < m_renderers.size(); i++)
	{
		//SetShader
		m_pImmediateContext->RSSetState(nullptr);

		m_pImmediateContext->IASetPrimitiveTopology(m_renderers[i]->GetTopology());
		m_pImmediateContext->UpdateSubresource(m_perObjectBuffer, 0, nullptr, &m_renderers[i]->GetObjectBuffer(), 0, 0);

		m_renderers[i]->Draw();
	}

}

void ShadowMap::CleanUp()
{
	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SHADOWN_MAP] = m_depthMapSRV;

	m_pImmediateContext->OMSetRenderTargets(8, m_shaderManager->GetEmptyRenderTargets(), NULL);

}

ShadowMap::~ShadowMap()
{
}

ID3D11ShaderResourceView ** ShadowMap::DepthMapSRV()
{
	return &m_depthMapSRV;
}

void ShadowMap::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}
