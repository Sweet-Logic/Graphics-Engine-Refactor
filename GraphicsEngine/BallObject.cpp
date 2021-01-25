#include "BallObject.h"
#include "MeshComponent.h"
#include "Texture2D.h"
#include "ObjLoader.h"

BallObject::BallObject() : SceneObject("BallObject"), IDrawable(false)
{
}


BallObject::~BallObject()
{
}

void BallObject::Initialize(ID3D11Device * _pd3dDevice)
{
	StaticMeshComponent = ObjLoader::GetInstance()->LoadMeshFromFile("ball.obj");
	StaticMeshComponent->load();
	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("maps/CarTextureMap.tga"));
}

void BallObject::Update(float deltaTime)
{
	SceneObject::Update(deltaTime);
}

void BallObject::Draw(ID3D11DeviceContext *& Context, UINT * stride, UINT * offset, ID3D11Buffer * Buffer)
{
//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);

}
