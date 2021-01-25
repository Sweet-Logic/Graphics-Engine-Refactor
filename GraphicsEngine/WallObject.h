#pragma once
#include "SceneObject.h"
#include "IDrawable.h"

class MeshComponent;
class Texture2D;

class WallObject :
	public SceneObject,
	public IDrawable
{
public:
	WallObject();
	~WallObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	MeshComponent* StaticMeshComponent;


	ID3D11ShaderResourceView* _texture;
	ID3D11Texture2D* WTexture;
	Texture2D* temp;

	ID3D11ShaderResourceView *const pSRV[1] = { NULL };

};
