#pragma once
#include "CubeObject.h"
class Shader;

class SkyMapObject :
	public CubeObject
{
public:
	SkyMapObject(std::string _objectName);
	~SkyMapObject();

	Shader* SKYMAP;
	ID3D11Texture2D* SMTexture = 0;

	ID3D11SamplerState* Sampler;
	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	ID3D11ShaderResourceView *const pSRV[1] = { NULL };

	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;

//	ID3D11Texture2D* _skytex;
	ID3D11ShaderResourceView* _skyTexview;

	XMFLOAT3 _cameraPosition = XMFLOAT3(0.0f,0.0f,0.0f);

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	virtual void Update(float deltaTime) override;

	void StartDraw(ID3D11DeviceContext *& Context);
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	void EndDraw(ID3D11DeviceContext *& Context);
};

