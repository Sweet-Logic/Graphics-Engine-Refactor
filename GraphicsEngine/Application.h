#ifndef _H_APPLICATION_
#define _H_APPLICATION_

#include <Windows.h>
#include "resource.h"
#include "utils/Singleton.h"

// struct BoundingSphere
// {
// 	BoundingSphere() : Center(0.0f, 0.0f, 0.0f), Radius(0.0f) {}
// 	XMFLOAT3 Center;
// 	float Radius;
// };


class Application : public Singleton<Application>
{
private:

	// static const int SMapSize = 2048;

	// ShadowMap* mSmap;
	// XMFLOAT4X4 mLightView;
	// XMFLOAT4X4 mLightProj;
	// XMFLOAT4X4 mShadowMapTransform;

	//void DrawSceneToShadowMap();

	// BoundingSphere mSceneBoundingSphere;
	// bool BlurOn = false;
	// bool BloomOn = false;

	// void BuildShadowTransform();
	// D3D11_VIEWPORT vp;

	// CameraObject* LookAtPitch;
	// CameraObject* LookDown;

	// std::vector<PointLight> PLight;
	// std::vector<DirectionalLight> DLight;
	// std::vector<SpotLight> SLight;

	// MatrialForCB basicMaterial;



	//double time = 1.0f;



	//CarBaseObject* _carReferance;

	

	//Swap Chain

	//RenderViews
	// ID3D11RenderTargetView* _pRenderTargetView; //Linked to back buffer
	// ID3D11RenderTargetView* _pFinalRenderTargetView;

	// ID3D11RenderTargetView* _pSceneTargetView;
	// ID3D11RenderTargetView* _pBlurTargetView;
	// ID3D11RenderTargetView* _pBloomTargetView;
	// ID3D11RenderTargetView* _pBrightnessMapTargetView;

	// //ShaderResourceView
	// ID3D11ShaderResourceView* _pBlurResourceView;
	// ID3D11ShaderResourceView* _pFinalRenderResourceView;

	// ID3D11ShaderResourceView* _pSceneResourceView;
	// ID3D11ShaderResourceView* _pBrightnessMapResourceView; 
	// ID3D11ShaderResourceView* _pBloomResourceView;
	// ID3D11ShaderResourceView* _pShaderOutputResourceView;



	//ID3D11BlendState* Transparency;

	//Shaders
	// Shader* _baseShader;
	// Shader* _blurShader;
	// Shader* _bloomShader;
	// Shader* _renderScene;
	// Shader* _brightnessMapShader;

	//Shader Input Layouts
	// ID3D11InputLayout*      _pVertexLayout;
	// ID3D11InputLayout*		_pScreenVertexLayout;

	//Buffer Objects

	// ID3D11Buffer*           _pScreenVertexBuffer;
	// ID3D11Buffer*           _pScreenIndexBuffer;

	// ID3D11Buffer*           _pCBFrame;
	// ID3D11Buffer*           _pConstantBufferSFX;
	// ID3D11Buffer*           _pConstantBufferBrightnessMap;
	// ID3D11Buffer*           _pCBObject;

	//Matrices
	//XMFLOAT4X4              _projection;
	
	//ConstBuffers
	// CBFrame Frame_ConstantBuffer;
	// ConstantBufferSFX sfxcb;
	// CBObject Object_ConstantBuffer;
	// ConstantBufferBrightnessMapping cbBM;

	//Wireframe
	//ID3D11RasterizerState* _wireFrame;

	//Depth
	// ID3D11DepthStencilView* _depthStencilView;
	// ID3D11Texture2D* _depthStencilBuffer;

	//textureSampler
	// ID3D11SamplerState* Sampler;
	// ID3D11SamplerState* shadow;

	//Textures
	// ID3D11Texture2D* _seneTexture;
	// ID3D11Texture2D* _finalRenderTexture;
	// ID3D11Texture2D* _blurTexture;
	// ID3D11Texture2D* _bloomTexture;
	// ID3D11Texture2D* _brightnessMapTexture;
	// ID3D11Texture2D* _sceneRender;
	// ID3D11Texture2D* _shaderOutput;



	double lastTime = 0.0f;
	double currentTime = 0.0f;

	//int blurLoopAmount = 1;

	//bool RenderInWireframe = false;

	//bool pressed = false;

private:
	//HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	//HRESULT InitDevice();
	void Cleanup();
	// HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	// HRESULT InitShadersAndInputLayout();
	// HRESULT InitVertexBuffer();
	// HRESULT InitIndexBuffer();

	//UINT _WindowHeight;
	//UINT _WindowWidth;

	//void BuildScene(std::string BuildFile);

public:
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	void Release();
	void Start() {};
	void Update();

	//void Draw();
	//void Resize();


	//static CameraObject* _currentCamera;

	// XMFLOAT3 GetVectorFrom(std::string string)
	// {
	// 	XMFLOAT3 output = XMFLOAT3(0, 0, 0);
	// 	int Xend = string.find(',');
	// 	int Yend = string.find(',', Xend+1);
	// 	int Zend = string.length();
	// 	float x;
	// 	float y; 
	// 	float z;
	// 	if (string.substr(0, Xend) == "PI")
	// 	{
	// 		x = XM_PI;
	// 	}
	// 	else
	// 	{
	// 		x = std::stof(string.substr(0, Xend));
	// 	}

	// 	if (string.substr(Xend+1, Yend - (Xend+1)) == "PI")
	// 	{
	// 		y = XM_PI;
	// 	}
	// 	else
	// 	{
	// 		y = std::stof(string.substr(Xend+1, Yend - (Xend+1)));
	// 	}

	// 	if (string.substr(Yend, Zend - Yend) == "PI")
	// 	{
	// 		z = XM_PI;
	// 	}
	// 	else
	// 	{
	// 		z = std::stof(string.substr(Yend+1, Zend - (Yend+1)));
	// 	}
	// 	output.x = x;
	// 	output.y = y;
	// 	output.z = z;


	// 	return output;
	// }
};
#endif //_H_APPLICATION_
