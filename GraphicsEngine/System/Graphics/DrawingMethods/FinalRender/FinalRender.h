#ifndef _FINAL_RENDER_H_
#define _FINAL_RENDER_H_

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>

#include "../../ShaderGlobals/ConstantBuffers.h"
#include "../../ShaderGlobals/ResourceBindings.h"


class Graphics;
class ShaderManager;
class RenderTargetView;
class Texture2D;
class ShaderResourceView;
class RenderTargetView;
class Renderer;
class VertexShader;
class PixelShader;

using namespace DirectX;

class FinalRender
{
public:
	void Initialise();
	void Release();

	void SetUp();
	void Execute();
	void CleanUp();

	ID3D11ShaderResourceView** DepthMapSRV() { return nullptr; }

	void SetSize(int width, int height);
private:
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
    float ClearColorb[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	std::vector<Renderer*> m_opaqueRenderers;
	std::vector<Renderer*> m_transparantRenderers;
//Device and context
	ID3D11DeviceContext*    m_pImmediateContext;
	ID3D11Device* m_pDevice = nullptr;
	ShaderManager* m_shaderManager = nullptr;

    ID3D11Buffer*           m_pScreenVertexBuffer;
	ID3D11Buffer*           m_pScreenIndexBuffer;
//Settings
	UINT m_width;
	UINT m_height;
	ResourceBindings::Flags m_resourcesInUse = ResourceBindings::NO_RESOURCE;

    PostProcessing::ScreenFX m_screenCB;

//Temp need replacing
    XMFLOAT4X4 m_projection;
    XMFLOAT4X4 m_view;
    XMFLOAT4X4 m_world;

//Viewport same
	D3D11_VIEWPORT m_Viewport;

//Shaders
	VertexShader* m_pVertexShader = nullptr;
	PixelShader* m_pPixelShader = nullptr;

//States
	ID3D11RasterizerState* m_depthRas = nullptr;
	ID3D11RasterizerState* m_wireframeRasterizerState = nullptr;
	ID3D11SamplerState* m_shadow = nullptr;
	ID3D11BlendState* m_transparncyBlendState = nullptr;

//Resouces
	ShaderResourceView* m_depthMapSRV = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;

	RenderTargetView* m_sceneRenderTarget = nullptr;
	RenderTargetView* m_brightnessMapTarget = nullptr;

	ShaderResourceView* m_sceneRenderResource = nullptr;
	ShaderResourceView* m_brightnessMapResource = nullptr;

    ID3D11Buffer* m_perSceneBuffer = nullptr;
    ID3D11Buffer* m_perFrameBuffer = nullptr;
    ID3D11Buffer* m_perObjectBuffer = nullptr;
    ID3D11Buffer* m_perPassBuffer = nullptr;
    ID3D11Buffer* m_screenSpaceBuffer = nullptr;

	Texture2D* m_sceneRender = nullptr;
	Texture2D* m_hdrBrightness = nullptr;
	
	Texture2D* m_depthStencilBuffer = nullptr;

//Shadred Resources
	ID3D11RenderTargetView* m_renderTagetViews[1] = {nullptr};
};



#endif //!_FINAL_RENDER_H_