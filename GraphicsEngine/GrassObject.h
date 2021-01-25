#pragma once
#include "SceneObject.h"
#include "IDrawable.h"
#include "Buffers.h"
#include <vector>
#include <random>

class Shader;

class GrassObject :
	public SceneObject,
	public IDrawable
{
public:

	void SetBounds(XMFLOAT3 min, XMFLOAT3 max) { _minBounds = min; _maxBounds = max; }
	void SetDensity(float density) { _density = density; }

	void GenerateGrass();

	

	virtual void Initialize(ID3D11Device* device) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	virtual void LoadGS(ID3D11DeviceContext *& Context);
	virtual void UnloadGS(ID3D11DeviceContext *& Context);


	GrassObject();
	~GrassObject();

private:
	ID3D11SamplerState* Sampler;

	ID3D11Buffer* _indexBuffer;
	ID3D11Buffer* _vertexBuffer;

	ID3D11Buffer* _grassInstance;

	ID3D11Device * _device;
	ID3D11RasterizerState* RSCullNone;

	XMFLOAT3 _minBounds = XMFLOAT3(100, 0, 100);
	XMFLOAT3 _maxBounds = XMFLOAT3(-100, 5, -100);

	//CBBillboardFrame _cbFrameBuffer;

	ID3D11Buffer* _frameBuffer;

	ID3D11Buffer* _grassBuffer;

	ID3DBlob* GS_Buffer;
	ID3D11GeometryShader* GS;

	float _density = 5;

	float GrassHeight = 10;
	float GrassWidth = 4.0f;

//	std::vector<CBPerGrass> GrassBlades;

	Shader* shaders;

	ID3D11InputLayout* _pVertexLayout;

	
};

