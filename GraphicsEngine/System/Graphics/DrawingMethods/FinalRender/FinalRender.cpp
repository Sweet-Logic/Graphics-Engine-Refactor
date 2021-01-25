// 	// Final Render
// 	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

// 	_pImmediateContext->VSSetShader(_renderScene->GetVS(), nullptr, 0);
// 	_pImmediateContext->PSSetShader(_renderScene->GetPS(), nullptr, 0);

// 	//_pImmediateContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

// 	// Set vertex buffer

// 	if (GetAsyncKeyState('P'))
// 	{
// 		_pImmediateContext->PSSetShaderResources(0, 1, mSmap->DepthMapSRV());
// 	}
// 	else 
// 	{
// 		_pImmediateContext->PSSetShaderResources(0, 1, &_pSceneResourceView);
// 	}
// 	_pImmediateContext->DrawIndexed(6, 0, 0);
// 	_pImmediateContext->PSSetShaderResources(0, 1, pSRV);

// 	_pSwapChain->Present(0, 0);

#include "FinalRender.h"
#include "../../Graphics.h"
#include "../../ShaderManager.h"
#include "../../../../Resource/Textures/Texture2DFactory.h"
#include "../../Views/RenderTargetViews/RenderTargetView.h"
#include "../../Views/ShaderResourceViews/ShaderResourceView.h"
#include "../../../../Object/Components/Renderer/RendererComponent.h"
#include "../../Shader.h"
#include "../../VertexLayouts/ScreenSpaceVertex.h"


void FinalRender::Initialise()
{
	HRESULT hr;
    Graphics* graphics = &Graphics::GetInstance();
    m_pImmediateContext = graphics->GetContext();
    m_pDevice = graphics->GetDevice();

	m_shaderManager = &ShaderManager::GetInstance();


 	// Setup the viewport
 	m_Viewport.Width =  (FLOAT)m_width;
 	m_Viewport.Height = (FLOAT)m_height;
 	m_Viewport.MinDepth = 0.0f;
 	m_Viewport.MaxDepth = 1.0f;
 	m_Viewport.TopLeftX = 0;
 	m_Viewport.TopLeftY = 0;

	// create Depth stencil
	DXGI_SAMPLE_DESC sample;
	sample.Count = 1;
	sample.Quality = 0;

	m_depthStencilBuffer = TEXTURE_2D_FACTORY::Create(
		(FLOAT)m_width,(FLOAT)m_height,1,1,DXGI_FORMAT_D24_UNORM_S8_UINT,
		sample,D3D11_USAGE_DEFAULT,	D3D11_BIND_DEPTH_STENCIL,0,0);

 	m_pDevice->CreateDepthStencilView(m_depthStencilBuffer->GetTexture(), nullptr, &m_depthStencilView);


	//Create textures for outputs
 	D3D11_RENDER_TARGET_VIEW_DESC RenTargetDesc;
 	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;

	// Create Texture to be written to

	m_sceneRender = TEXTURE_2D_FACTORY::Create(
		(FLOAT)m_width,(FLOAT)m_height,1,1,DXGI_FORMAT_R8G8B8A8_UNORM,
		sample,D3D11_USAGE_DEFAULT,	D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,0,0);

	m_sceneRenderTarget = new RenderTargetView(m_sceneRender);
	m_sceneRenderResource = new ShaderResourceView(m_sceneRender);

	m_hdrBrightness = TEXTURE_2D_FACTORY::Create(
		(FLOAT)m_width,(FLOAT)m_height,1,1,DXGI_FORMAT_R8G8B8A8_UNORM,
		sample,D3D11_USAGE_DEFAULT,	D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,0,0);

	m_brightnessMapTarget = new RenderTargetView(m_hdrBrightness);
	m_brightnessMapResource = new ShaderResourceView(m_hdrBrightness);

	// wireframe rasterizer;
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.FillMode = D3D11_FILL_WIREFRAME;
	wfdesc.CullMode = D3D11_CULL_NONE;
	hr = m_pDevice->CreateRasterizerState(&wfdesc, &m_wireframeRasterizerState);


    m_renderTagetViews[0] = nullptr;
    m_renderTagetViews[1] = nullptr;

	//Load the required shaders
	Shader* shaderArray[2] = 
	{
		nullptr,
		nullptr
	};
	ShaderManager::GetInstance().LoadShaders(shaderArray, 2, L"RenderToScene.fx",(ShaderType)(E_VERTEX | E_PIXEL));
	m_pVertexShader = (VertexShader*)shaderArray[0];
	m_pPixelShader = (PixelShader*)shaderArray[1];

	//Create Input Layout
	UINT numElements = ARRAYSIZE(ScreenSpace::vertexLayout);
	hr = m_pDevice->CreateInputLayout(ScreenSpace::vertexLayout, numElements, m_pVertexShader->m_blob->GetBufferPointer(),
	m_pVertexShader->m_blob->GetBufferSize(), &m_pVertexShader->m_inputLayout);

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

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PostProcessing::ScreenFX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = m_pDevice->CreateBuffer(&bd, nullptr, &m_screenSpaceBuffer);
	
	float fov = 90.f * (180.0f/XM_PI);

	XMStoreFloat4x4(&m_projection, XMMatrixPerspectiveFovLH(fov, m_width / (FLOAT)m_height, 0.01f, 100.0f));
	
	InitVertexBuffer();
	InitIndexBuffer();
}

HRESULT FinalRender::InitVertexBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC bd;


	D3D11_SUBRESOURCE_DATA InitData;


	ScreenSpace::ScreenVertex sfxPlaneVerts[] =
	{	//Pos								//Tex				
		{ XMFLOAT2(-1.0f, 1.0f),		XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT2(1.0f, 1.0f ),	XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT2(-1.0f,-1.0f),		XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT2(1.0f,-1.0f ),	XMFLOAT2(1.0f,1.0f)},
	};

	D3D11_BUFFER_DESC sfxbd;
	ZeroMemory(&sfxbd, sizeof(sfxbd));
	sfxbd.Usage = D3D11_USAGE_DEFAULT;
	sfxbd.ByteWidth = sizeof(ScreenSpace::ScreenVertex) * 4;
	sfxbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sfxbd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sfxInitData;
	ZeroMemory(&sfxInitData, sizeof(sfxInitData));
	sfxInitData.pSysMem = sfxPlaneVerts;

	hr = m_pDevice->CreateBuffer(&sfxbd, &sfxInitData, &m_pScreenVertexBuffer);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT FinalRender::InitIndexBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC bd;


	D3D11_SUBRESOURCE_DATA InitData;

	WORD sfxPlane[] =
	{
		0,1,2,
		2,1,3,
	};

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = sfxPlane;
	hr = m_pDevice->CreateBuffer(&bd, &InitData, &m_pScreenIndexBuffer);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

void FinalRender::Release()
{
	m_shaderManager->ReleaseChild(m_depthRas);
	m_shaderManager->ReleaseChild(m_pVertexShader->m_DX11Shader);
	m_shaderManager->ReleaseChild(m_pPixelShader->m_DX11Shader);
	m_shaderManager->ReleaseChild(m_wireframeRasterizerState);
	m_shaderManager->ReleaseChild(m_shadow);
	m_shaderManager->ReleaseChild(m_transparncyBlendState);
	m_shaderManager->ReleaseChild(m_depthMapSRV->GetShaderResourceView());
	m_shaderManager->ReleaseChild(m_depthStencilView);
	m_shaderManager->ReleaseChild(m_sceneRenderTarget->GetRenderTarget());
	m_shaderManager->ReleaseChild(m_brightnessMapTarget->GetRenderTarget());
	m_shaderManager->ReleaseChild(m_sceneRenderResource->GetShaderResourceView());
	m_shaderManager->ReleaseChild(m_brightnessMapResource->GetShaderResourceView());
    m_shaderManager->ReleaseChild(m_perSceneBuffer);
    m_shaderManager->ReleaseChild(m_perFrameBuffer);
    m_shaderManager->ReleaseChild(m_perObjectBuffer);
    m_shaderManager->ReleaseChild(m_perPassBuffer);
}

void FinalRender::SetUp()
{


	//Set primitive topology

    /////////

	// Bind set render targets in to array
	m_renderTagetViews[0] = Graphics::GetInstance().GetRenderTarget();
	// Unbind the resources that are linked to the render targets
	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SCENE_RENDER] = nullptr;
	m_shaderManager->GetResources()[ResourceBindings::INDEX_HDR_BRIGHTNESS_MAP] = nullptr;

	// Clear All render targets
	m_pImmediateContext->ClearRenderTargetView(m_renderTagetViews[0], ClearColorb);

	// Clear Depth and Stencils
	m_pImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set Shaders
	m_pImmediateContext->VSSetShader(m_pVertexShader->m_DX11Shader, nullptr, 0);
	m_pImmediateContext->PSSetShader(m_pPixelShader->m_DX11Shader, nullptr, 0);

	// Set the input layout for this vertex shader
	m_pImmediateContext->IASetInputLayout(m_pVertexShader->m_inputLayout);

	// Set the view ports
	m_pImmediateContext->RSSetViewports(1, &m_Viewport); // Needs to be the same dimentions as the output texture(s)

	// Set the output textures
	m_pImmediateContext->OMSetRenderTargets(2, m_renderTagetViews, m_depthStencilView);

	// Set per Scene Data
	
	// Populate per Frame Data
	m_pImmediateContext->UpdateSubresource(m_screenSpaceBuffer, 0, nullptr, &m_screenCB, 0, 0);

	// Set per Frame Constant Buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_screenSpaceBuffer);
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_screenSpaceBuffer);
	
	// Set Rastariser State
	m_pImmediateContext->RSSetState(nullptr);

	//XMStoreFloat4(&(Frame_ConstantBuffer.EyePosW), _currentCamera->GetWorldPosition());

	// Set primitive topology
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void FinalRender::Execute()
{
	UINT stride = sizeof(ScreenSpace::ScreenVertex);
	UINT offset = 0;

    m_pImmediateContext->RSSetState(nullptr);
    
	//Set vertex buffer
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pScreenVertexBuffer, &stride, &offset);

	//Set index buffer
	m_pImmediateContext->IASetIndexBuffer(m_pScreenIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	m_pImmediateContext->PSSetShaderResources(0, 1, &m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SCENE_RENDER]);

    m_pImmediateContext->DrawIndexed(6, 0, 0);

	m_pImmediateContext->OMSetRenderTargets(8, m_shaderManager->GetEmptyRenderTargets(), NULL);
}

void FinalRender::CleanUp()
{
	m_renderTagetViews[0] = nullptr;
	m_renderTagetViews[1] = nullptr;

	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SCENE_RENDER] = m_sceneRenderResource->GetShaderResourceView();
	m_shaderManager->GetResources()[ResourceBindings::INDEX_HDR_BRIGHTNESS_MAP] = m_brightnessMapResource->GetShaderResourceView();

	m_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);
}

void FinalRender::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}
