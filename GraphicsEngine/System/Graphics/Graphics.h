#ifndef _H_GRAPHICS_
#define _H_GRAPHICS_

#include "../System.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "../window/Window.h"

#include "Shader.h"

using namespace DirectX;

class ShaderManager;

class Graphics : public System<Graphics>
{
public:
    static Graphics* s_instance;

private:
    D3D_DRIVER_TYPE         m_driverType;

	D3D_FEATURE_LEVEL       m_featureLevel;

	//Device Referances
	ID3D11Device*           m_pd3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;

	IDXGISwapChain*         m_pSwapChain;
    
    ID3D11RenderTargetView* m_pRenderTargetView;
public:
    ID3D11Device* const GetDevice() { return m_pd3dDevice;}
    ID3D11DeviceContext* const GetContext() {return m_pImmediateContext;}

    void SetDriverType(D3D_DRIVER_TYPE driverType) { m_driverType = driverType; }
    void SetFeatureLevel(D3D_FEATURE_LEVEL featureLevel) { m_featureLevel = featureLevel; }

    IDXGISwapChain* GetSwapChain() {return m_pSwapChain;} 
    ID3D11RenderTargetView* GetRenderTarget() {return m_pRenderTargetView;}
private:
    ShaderManager* m_shaderManagerInstance = nullptr;
public:
    
    HRESULT Initialise() override;
	void Update() override;
    void Release() override;

	void LoadShader() {};
	void CreateRenderTarget() {};

    void ScreenSizeChanged();

    void ClearCurrentRenderTarget();
};

#endif //_H_GRAPHICS_