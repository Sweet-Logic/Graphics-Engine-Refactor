#pragma once
#include "SceneObject.h"
#include "IDrawable.h"

class MeshComponent;

class GoalObject:
	public SceneObject,
	public IDrawable
{
public:
	GoalObject();
	~GoalObject();


	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	MeshComponent* StaticMeshComponent;
};

