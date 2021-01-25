#ifndef _SHADOW_MAPPING_H_
#define _SHADOW_MAPPING_H_

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>

#include "../../ShaderGlobals/Lighting.h"
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

class ShadowMap
{
public:
	void Initialise();
	void Release();

	void SetUp();
	void Execute();
	void CleanUp();

	~ShadowMap();

	ID3D11ShaderResourceView** DepthMapSRV();

	void SetSize(int width, int height);

private:
	void BuildShadowTransform(Lighting* currentLight, XMFLOAT4X4& view, XMFLOAT4X4& proj, XMFLOAT4X4& transform);
	std::vector<Renderer*> m_renderers;
	float ClearColorb[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Device and context
	ID3D11DeviceContext*    m_pImmediateContext;
	ID3D11Device* m_pDevice;	
	ShaderManager* m_shaderManager;
//Settings
	UINT m_width;
	UINT m_height;
	MainConstants::Frame m_frameCB;
	Lighting* m_shadowSource;

//Viewport same
	D3D11_VIEWPORT mViewport;

//Shaders
	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;
//States
	ID3D11RasterizerState* m_depthRas;

//Resouces
	ID3D11ShaderResourceView* m_depthMapSRV;
	ID3D11DepthStencilView* m_depthMapDSV;
	ID3D11RenderTargetView* m_emptyView[1] = { NULL };

	ID3D11Buffer* m_perSceneBuffer;
	ID3D11Buffer* m_perFrameBuffer;
	ID3D11Buffer* m_perObjectBuffer;
	ID3D11Buffer* m_perPassBuffer;
};



#endif //!_SHADOW_MAPPING_H_