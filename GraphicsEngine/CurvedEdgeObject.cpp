#include "CurvedEdgeObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"



CurvedEdgeObject::CurvedEdgeObject() : SceneObject("Curve"), IDrawable(true)
{
}


CurvedEdgeObject::~CurvedEdgeObject()
{
}



void CurvedEdgeObject::Initialize(ID3D11Device* _pd3dDevice)
{
	StaticMeshComponent = new MeshComponent();

	// Create vertex buffer
	StaticMeshComponent = ObjLoader::GetInstance()->LoadMeshFromFile("WallCurve.obj");
	StaticMeshComponent->load();
	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("wallCurveTexture.tga"));

}

void CurvedEdgeObject::Update(float deltaTime)
{

	SceneObject::Update(deltaTime);
}

void CurvedEdgeObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{
//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);
}