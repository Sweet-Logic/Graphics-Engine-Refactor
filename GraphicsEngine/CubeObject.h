#pragma once
#include "SceneObject.h"
#include "IDrawable.h"


class MeshComponent;

class CubeObject :
	public SceneObject,
	public IDrawable
{
public:
	CubeObject(std::string _objectName, bool AddToList = true);
	~CubeObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer) override;

	MeshComponent* StaticMeshComponent;

	

	
};

