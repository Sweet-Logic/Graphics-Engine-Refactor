#include "CrateObject.h"
#include "MeshComponent.h"



CrateObject::CrateObject(std::string _objectName) : CubeObject(_objectName)
{
}


CrateObject::~CrateObject()
{
}

void CrateObject::Initialize(ID3D11Device* _pd3dDevice)
{
	CubeObject::Initialize(_pd3dDevice);

	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("testdiff.tga"));
	StaticMeshComponent->SetTexture(Map::Bump, new Texture2D("normal.tga"));

	ScaleObject(XMVectorSet(10.0f, 10.0f, 10.0f, 1.0f));

	TranslateObject(XMVectorSet(0.0f, 10.0f, 0.0f, 1.0f));

}
