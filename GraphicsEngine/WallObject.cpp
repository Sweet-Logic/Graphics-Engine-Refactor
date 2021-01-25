#include "WallObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"
#include "DDSTextureLoader.h"


WallObject::WallObject() : SceneObject("Wall"), IDrawable(false)
{
}


WallObject::~WallObject()
{
}

void WallObject::Initialize(ID3D11Device* _pd3dDevice)
{

	StaticMeshComponent = new MeshComponent();
	StaticMeshComponent = ObjLoader::GetInstance()->LoadMeshFromFile("WallCeilling.obj");
	StaticMeshComponent->load();
	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("ChainLink.dds"));

//	ObjectConstantBuffer.clipTexture = 1.0f;

}

void WallObject::Update(float deltaTime)
{

	SceneObject::Update(deltaTime);
}

void WallObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);

}