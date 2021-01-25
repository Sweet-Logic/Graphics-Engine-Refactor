#pragma once
#include "SceneObject.h"
#include "IDrawable.h"
#include "Buffers.h"
#include <vector>


class Texture2D;

struct BillboardData
{
	Texture2D* Texture;
	ID3D11Buffer* _vertexBuffer;
//	CBPerBillboard _cbBillboardBuffer;
	XMFLOAT3 Position;
};

class BillboardObject :
	public SceneObject,
	public IDrawable
{
public:


	static BillboardObject* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new BillboardObject();
		}
		return instance;
	}

//	CBBillboardFrame _cbFrameBuffer;
	ID3D11Buffer* _frameBuffer;

	ID3D11Buffer* _billboardBuffer;

	ID3DBlob* GS_Buffer;
	ID3D11GeometryShader* GS;


	std::vector<BillboardData> billboards;

	virtual void Initialize(ID3D11Device* device) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	virtual void LoadGS(ID3D11DeviceContext *& Context);
	virtual void UnloadGS(ID3D11DeviceContext *& Context);

	void AddBillboard(XMFLOAT3 position, Texture2D* texture);

//	void UpdateCameraPosition(XMFLOAT4 newCamPos) { _cbFrameBuffer.CamPos = newCamPos; };

private:
	BillboardObject();
	~BillboardObject();

	static BillboardObject* instance;
	ID3D11SamplerState* Sampler;

	ID3D11Buffer* _indexBuffer;

	ID3D11Device * _device;
	ID3D11RasterizerState* RSCullNone;


};

