#pragma once
#include "IDrawable.h"
#include "SceneObject.h"

class MeshComponent;


class PyrimidObject :
	public SceneObject,
	public IDrawable
{
public:
	PyrimidObject();
	~PyrimidObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	void Update(float deltaTime) override;
	void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer);

	MeshComponent* StaticMeshComponent;
};

