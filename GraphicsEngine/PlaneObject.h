#pragma once
#include "SceneObject.h"
#include "IDrawable.h"

class MeshComponent;


class PlaneObject :
	public SceneObject,
	public IDrawable
{
public:
	PlaneObject();
	~PlaneObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;


	void Update(float deltaTime) override;
	void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer);
	MeshComponent* StaticMeshComponent;
};

