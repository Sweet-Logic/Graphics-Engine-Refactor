#include "CubeObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"


CubeObject::CubeObject(std::string _objectName, bool AddToList) : SceneObject(_objectName, AddToList), IDrawable(false)
{
}


CubeObject::~CubeObject()
{
}

void CubeObject::Initialize(ID3D11Device* _pd3dDevice)
{
	StaticMeshComponent = new MeshComponent();

	// Create vertex buffer

	Vertex vertices[] =
	{	//Pos							//Tex					//Normals							//Tangents
		{ XMFLOAT3(-1.0f, 1.0f,-1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(0.0f,0.0f,-1.0f,0.0f),		XMFLOAT3(1,0,0) },//Front
		{ XMFLOAT3(1.0f, 1.0f,-1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(0.0f,0.0f,-1.0f,0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(1.0f,-1.0f,-1.0f),	XMFLOAT2(1.0f,1.0f),	XMFLOAT4(0.0f,0.0f,-1.0f, 0.0f),	XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-1.0f,-1.0f,-1.0f),	XMFLOAT2(0.0f,1.0f),	XMFLOAT4(0.0f,0.0f,-1.0f,0.0f),		XMFLOAT3(1,0,0) },

		{ XMFLOAT3(1.0f, 1.0f,-1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,1) },//Right
		{ XMFLOAT3(1.0f, 1.0f,1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,1) },
		{ XMFLOAT3(1.0f,-1.0f,1.0f),	XMFLOAT2(1.0f,1.0f),	XMFLOAT4(1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,1) },
		{ XMFLOAT3(1.0f,-1.0f,-1.0f),	XMFLOAT2(0.0f,1.0f),	XMFLOAT4(1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,1) },

		{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(0.0f,0.0f,1.0f,0.0f),		XMFLOAT3(-1,0,0) },//Back
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(0.0f,0.0f,1.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(-1.0f,-1.0f, 1.0f),  XMFLOAT2(1.0f,1.0f),	XMFLOAT4(0.0f,0.0f,1.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT2(0.0f,1.0f),	XMFLOAT4(0.0f,0.0f,1.0f,0.0f),		XMFLOAT3(-1,0,0) },

		{ XMFLOAT3(-1.0f, 1.0f,1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(-1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,-1) },//Left
		{ XMFLOAT3(-1.0f, 1.0f,-1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(-1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.0f,-1.0f,-1.0f),	XMFLOAT2(1.0f,1.0f),	XMFLOAT4(-1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.0f,-1.0f, 1.0f),	XMFLOAT2(0.0f,1.0f),	XMFLOAT4(-1.0f,0.0f,0.0f,0.0f),		XMFLOAT3(0,0,-1) },

		{ XMFLOAT3(-1.0f, 1.0f,1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },//Top
		{ XMFLOAT3(1.0f, 1.0f,1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(1.0f,1.0f,-1.0f),	XMFLOAT2(1.0f,1.0f),	XMFLOAT4(0.0f,1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(-1.0f,1.0f,-1.0f),	XMFLOAT2(0.0f,1.0f),	XMFLOAT4(0.0f,1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },

		{ XMFLOAT3(-1.0f, -1.0f,-1.0f),	XMFLOAT2(0.0f,0.0f),	XMFLOAT4(0.0f,-1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },//Bottom
		{ XMFLOAT3(1.0f, -1.0f,-1.0f),	XMFLOAT2(1.0f,0.0f),	XMFLOAT4(0.0f,-1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(1.0f,-1.0f,1.0f),	XMFLOAT2(1.0f,1.0f),	XMFLOAT4(0.0f,-1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },
		{ XMFLOAT3(-1.0f,-1.0f,1.0f),	XMFLOAT2(0.0f,1.0f),	XMFLOAT4(0.0f,-1.0f,0.0f,0.0f),		XMFLOAT3(-1,0,0) },
	};

	WORD indices[] =
	{
		//Front
		0,1,3,
		1,2,3,
		//Right
		4,5,7,
		5,6,7,
		//Back
		8,9,11,
		9,10,11,
		//Left
		12,13,15,
		13,14,15,
		//Top
		16,17,19,
		17,18,19,
		//Bottom
		20,21,23,
		21,22,23,
	};

	
	StaticMeshComponent = ObjLoader::GetInstance()->CreateMesh("cubeObj", vertices, indices, 24, 36);
	StaticMeshComponent->load();

}

void CubeObject::Update(float deltaTime)
{

	SceneObject::Update(deltaTime);
}

void CubeObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{
//	Context->UpdateSubresource(Buffer, 0, nullptr, &GetObjectCB(), 0, 0);

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);
}
