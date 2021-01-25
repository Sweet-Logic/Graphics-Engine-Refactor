#include "Graphics.h"

#include "ShaderManager.h"


Graphics* Graphics::s_instance = nullptr;

HRESULT Graphics::Initialise()
{
    HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	Window &alias = Window::GetInstance();

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = alias.GetWidth();
	sd.BufferDesc.Height = alias.GetWidth();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = alias.GetWindowHandle();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, m_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	ID3D11Texture2D* pBackBuffer = nullptr;

	// Create a render target view
 	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

 	if (FAILED(hr))
 		return hr;


 	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);

 	pBackBuffer->Release();

	if (FAILED(hr))
		return hr;
	
	m_shaderManagerInstance = &ShaderManager::GetInstance();
	m_shaderManagerInstance->Initialise();
}

void Graphics::Release()
{
	//Release Shaders <-- maybe a resource so let that handle this???? (same with textures)
	//Release RTV
	//Release Buffers
	//Release Layouts
	//Release Stencils
	//Release Rastariser States
	//Release SRV
	//Release Samplers
	if(m_pSwapChain)			m_pSwapChain->Release();
	if(m_pImmediateContext)		m_pImmediateContext->Release();
	if(m_pd3dDevice)			m_pd3dDevice->Release();
}

void Graphics::Update()
{
	m_shaderManagerInstance->Update();
	//Clear render Target
	//Clear Resource Views
	//Clear Render Target Views
	//Clear Depth Stencil
	
	//Set Input Layout
	
	//Start Passes
	m_shaderManagerInstance->Draw();
	
	
}

void Graphics::ScreenSizeChanged()
{
    // ::TODO:: Work out how to do screen resizing : https://docs.microsoft.com/en-gb/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi?redirectedfrom=MSDN#care-and-feeding-of-the-swap-chain
}



