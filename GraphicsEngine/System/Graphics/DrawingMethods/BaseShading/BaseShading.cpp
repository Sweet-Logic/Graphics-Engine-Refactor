#include "BaseShading.h"
#include "../../Graphics.h"
#include "../../ShaderManager.h"
#include "../../../../Resource/Textures/Texture2DFactory.h"
#include "../../Views/RenderTargetViews/RenderTargetView.h"
#include "../../Views/ShaderResourceViews/ShaderResourceView.h"
#include "../../VertexLayouts/BaseVertex.h"
#include "../../../../Object/Components/Renderer/RendererComponent.h"
#include "../../Shader.h"
#include "../../VertexLayouts/BaseVertex.h"


void BaseShading::Initialise()
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
	ShaderManager::GetInstance().LoadShaders(shaderArray, 2, L"DX11 Framework.fx",(ShaderType)(E_VERTEX | E_PIXEL));
	m_pVertexShader = (VertexShader*)shaderArray[0];
	m_pPixelShader = (PixelShader*)shaderArray[1];

	//Create Input Layout
	UINT numElements = ARRAYSIZE(vertexLayout);
	hr = m_pDevice->CreateInputLayout(vertexLayout, numElements, m_pVertexShader->m_blob->GetBufferPointer(),
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

	float fov = 90.f * (180.0f/XM_PI);

	XMStoreFloat4x4(&m_projection, XMMatrixPerspectiveFovLH(fov, m_width / (FLOAT)m_height, 0.01f, 100.0f));
}

void BaseShading::Release()
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

void BaseShading::SetUp()
{
	// Bind set render targets in to array
	m_renderTagetViews[0] = m_sceneRenderTarget->GetRenderTarget();
	m_renderTagetViews[1] = m_brightnessMapTarget->GetRenderTarget();
	// Unbind the resources that are linked to the render targets
	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SCENE_RENDER] = nullptr;
	m_shaderManager->GetResources()[ResourceBindings::INDEX_HDR_BRIGHTNESS_MAP] = nullptr;

	// Clear All render targets
	m_pImmediateContext->ClearRenderTargetView(m_renderTagetViews[0], ClearColorb);
	m_pImmediateContext->ClearRenderTargetView(m_renderTagetViews[1], ClearColorb);

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
	//m_frameCB.View = _currentCamera->GetTransposedViewMatrix();
	m_frameCB.Projection = XMMatrixTranspose(XMLoadFloat4x4(&m_projection));

	// Set per Frame Constant Buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_perFrameBuffer);
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_perFrameBuffer);
	
	// Set per Object Constant Buffer
	m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_perObjectBuffer);
	m_pImmediateContext->PSSetConstantBuffers(1, 1, &m_perObjectBuffer);

	// Set per Pass Constant Buffer
	m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_perPassBuffer);
	m_pImmediateContext->PSSetConstantBuffers(1, 1, &m_perPassBuffer);
	
	// Set Rastariser State
	m_pImmediateContext->RSSetState(nullptr);

	//XMStoreFloat4(&(Frame_ConstantBuffer.EyePosW), _currentCamera->GetWorldPosition());

	// Set primitive topology
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void BaseShading::Execute()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	for (int i = 0; i < m_opaqueRenderers.size(); ++i)
	{
		//SetShader
		if(m_opaqueRenderers[i]->RenderWireframe())
			m_pImmediateContext->RSSetState(m_wireframeRasterizerState);
		else
			m_pImmediateContext->RSSetState(nullptr);
		
		m_pImmediateContext->IASetPrimitiveTopology(m_transparantRenderers[i]->GetTopology());
		m_pImmediateContext->IASetPrimitiveTopology(m_opaqueRenderers[i]->GetTopology());
		m_pImmediateContext->UpdateSubresource(m_perObjectBuffer, 0, nullptr, &m_opaqueRenderers[i]->GetObjectBuffer(), 0, 0);

		m_opaqueRenderers[i]->Draw();//?
		//	m_pImmediateContext->UpdateSubresource(_pCBObject, 0, nullptr, &temp->val->GetObjectCB(), 0, 0);

		//	toDraw->Draw(_pImmediateContext, &stride, &offset, _pCBObject);
	}

	//Set blend Factor
	float blendFactor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	m_pImmediateContext->OMSetBlendState(m_transparncyBlendState, blendFactor, 0xffffffff);

	for (int i = 0; i < m_transparantRenderers.size(); i++)
	{
		//SetShader
		if(m_transparantRenderers[i]->RenderWireframe())
			m_pImmediateContext->RSSetState(m_wireframeRasterizerState);
		else
			m_pImmediateContext->RSSetState(nullptr);
		
		m_pImmediateContext->IASetPrimitiveTopology(m_transparantRenderers[i]->GetTopology());
		m_transparantRenderers[i]->GetObjectBuffer();
		m_pImmediateContext->UpdateSubresource(m_perObjectBuffer, 0, nullptr, &m_transparantRenderers[i]->GetObjectBuffer(), 0, 0);

		m_transparantRenderers[i]->Draw();//?
		//	m_pImmediateContext->UpdateSubresource(_pCBObject, 0, nullptr, &temp->val->GetObjectCB(), 0, 0);

		//	toDraw->Draw(_pImmediateContext, &stride, &offset, _pCBObject);
	}
	m_pImmediateContext->OMSetRenderTargets(8, m_shaderManager->GetEmptyRenderTargets(), NULL);
}

void BaseShading::CleanUp()
{
	m_renderTagetViews[0] = nullptr;
	m_renderTagetViews[1] = nullptr;

	m_shaderManager->GetResources()[ResourceBindings::INDEX_GLOBAL_SCENE_RENDER] = m_sceneRenderResource->GetShaderResourceView();
	m_shaderManager->GetResources()[ResourceBindings::INDEX_HDR_BRIGHTNESS_MAP] = m_brightnessMapResource->GetShaderResourceView();

	m_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);
}

void BaseShading::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}
