#include "PyrimidObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"


PyrimidObject::PyrimidObject() : SceneObject("PyrimidObject"), IDrawable(false)
{
}


PyrimidObject::~PyrimidObject()
{
}



void PyrimidObject::Initialize(ID3D11Device* _pd3dDevice)
{

	StaticMeshComponent = new MeshComponent();
	// Create vertex buffer

	Vertex vertices[] =
	{	//Pos								//Tex						//Normals									//Tangents
		{ XMFLOAT3(0.0f, 1.0f,0.0f),		XMFLOAT2(-1.0f,-1.0f),		XMFLOAT4(0.0f, 1.0f,0.0f, 0.0f),			XMFLOAT3(0,0,1) },
	{ XMFLOAT3(1.0f, -1.0f,-1.0f),		XMFLOAT2(-1.0f,-1.0f),		XMFLOAT4(1.0f, -1.0f,-1.0f, 0.0f),			XMFLOAT3(0,0,1) },
	{ XMFLOAT3(1.0f,-1.0f,1.0f),		XMFLOAT2(-1.0f,-1.0f),		XMFLOAT4(1.0f,-1.0f,1.0f, 0.0f),			XMFLOAT3(0,0,1) },
	{ XMFLOAT3(-1.0f,-1.0f,1.0f),		XMFLOAT2(-1.0f,-1.0f),		XMFLOAT4(-1.0f,-1.0f,1.0f, 0.0f),			XMFLOAT3(0,0,1) },
	{ XMFLOAT3(-1.0f,-1.0f,-1.0f),		XMFLOAT2(-1.0f,-1.0f),		XMFLOAT4(-1.0f, -1.0f, -1.0f, 0.0f),		XMFLOAT3(0,0,1) },

	};

	WORD indices[] =
	{
		//Front
		0,2,1,
		//Left
		0,3,2,
		//Back
		0,4,3,
		//Right
		0,1,4,
		//Bottom
		1,3,4,
		2,3,1,
	};


	StaticMeshComponent = ObjLoader::GetInstance()->CreateMesh("pyrimidObj", vertices, indices, 5, 18);
}

void PyrimidObject::Update(float deltaTime)
{
	TranslateObject(XMVectorSet(2.0f, 2.0f, 2.0f, 1.0f));
	SceneObject::Update(deltaTime);

}

void PyrimidObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);
}