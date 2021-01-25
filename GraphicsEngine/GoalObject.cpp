#include "GoalObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"



GoalObject::GoalObject() : SceneObject("Goal"), IDrawable(false)
{
}


GoalObject::~GoalObject()
{
}

void GoalObject::Initialize(ID3D11Device* _pd3dDevice)
{
	StaticMeshComponent = new MeshComponent();
	StaticMeshComponent = ObjLoader::GetInstance()->LoadMeshFromFile("Goal.obj");
	StaticMeshComponent->load();

}

void GoalObject::Update(float deltaTime)
{
	SceneObject::Update(deltaTime);
}

void GoalObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);


	//RotateObject(XMVectorSet(0.0f, XM_PI, 0.0f, 1.0f));
	//TranslateObject(XMVectorSet(0.0f, 0.0f, 1285.0f, 1.0f));
	//SceneObject::Update(0.0f);
	//StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);
}