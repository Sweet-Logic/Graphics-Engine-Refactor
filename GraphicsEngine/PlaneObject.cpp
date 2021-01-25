#include "PlaneObject.h"
#include "MeshComponent.h"
#include "MaterialLibaryLoader.h"
#include "ObjLoader.h"


PlaneObject::PlaneObject(): SceneObject("planeObject"), IDrawable(false)
{
}


PlaneObject::~PlaneObject()
{
}

void PlaneObject::Initialize(ID3D11Device* _pd3dDevice)
{
	StaticMeshComponent = new MeshComponent();
	// Create vertex buffer

	float width = 4100;
	float depth = 5500;

	int m = 12;
	int n = 12;

	float dX = width / (n-1);
	float dZ = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	
	Vertex* vert = new Vertex[(m*n)];

	int k = 0;
	for (int i = 0; i < m; i++)
	{
		float z =  ((depth) * 0.5) - (i * dZ);
		for (int j = 0; j < n; j++)
		{
			float x = -((width) * 0.5) + j * dX;
			vert[i*n + j].Pos = XMFLOAT3(x, 0.0f, z);

			vert[k].TexCoords.x = i;
			vert[k].TexCoords.y = j;

			vert[k].Normal = { 0,1,0,0 };
			vert[k].Tangent = { 1,0,0 };
			k++;
		}
	}

	int triCount = (m - 1) * (n - 1) * 2;

	WORD* ind = new WORD[triCount*3];

	k = 0;
	for (int i = 0; i < m-1; i++)
	{
		for (int j = 0; j < n-1; j++)
		{
			k ++;
			ind[k*6 - 6] = i * m + j;
			ind[k*6 - 5] = i * m + j + 1;
			ind[k*6 - 4] = (i+1)* m + j;
				
			ind[k*6 - 3] = (i + 1)* m + j;
			ind[k*6 - 2] = i * m + j + 1;
			ind[k*6 - 1] = (i + 1)* m + j + 1;
		}
	}

	

	Vertex vertices[] =
	{	//Pos							//Tex						//Normals							//Tangents
		{ XMFLOAT3(4.0f,0.0f, 4.0f),	XMFLOAT2(1.0f,0.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(4.0f,0.0f, 2.0f),	XMFLOAT2(1.0f,0.25f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(4.0f,0.0f, 0.0f),	XMFLOAT2(1.0f,0.5f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(4.0f,0.0f,-2.0f),	XMFLOAT2(1.0f,0.75f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(4.0f,0.0f,-4.0f),	XMFLOAT2(1.0f,1.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(2.0f,0.0f, 4.0f),	XMFLOAT2(0.75f,0.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(2.0f,0.0f, 2.0f),	XMFLOAT2(0.75f,0.25f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(2.0f,0.0f, 0.0f),	XMFLOAT2(0.75f,0.5f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(2.0f,0.0f,-2.0f),	XMFLOAT2(0.75f,0.75f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(2.0f,0.0f,-4.0f),	XMFLOAT2(0.75f,1.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(0.0f,0.0f, 4.0f),	XMFLOAT2(0.5f ,0.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(0.0f,0.0f, 2.0f),	XMFLOAT2(0.5f ,0.25f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(0.0f,0.0f, 0.0f),	XMFLOAT2(0.5f ,0.5f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(0.0f,0.0f,-2.0f),	XMFLOAT2(0.5f ,0.75f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(0.0f,0.0f,-4.0f),	XMFLOAT2(0.5f ,1.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-2.0f,0.0f, 4.0f),	XMFLOAT2(0.25f,0.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-2.0f,0.0f, 2.0f),	XMFLOAT2(0.25f,0.25f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-2.0f,0.0f, 0.0f),	XMFLOAT2(0.25f,0.5f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-2.0f,0.0f,-2.0f),	XMFLOAT2(0.25f,0.75f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-2.0f,0.0f,-4.0f),	XMFLOAT2(0.25f,1.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-4.0f,0.0f, 4.0f),	XMFLOAT2(0.0f ,0.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-4.0f,0.0f, 2.0f),	XMFLOAT2(0.0f ,0.25f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-4.0f,0.0f, 0.0f),	XMFLOAT2(0.0f ,0.5f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-4.0f,0.0f,-2.0f),	XMFLOAT2(0.0f ,0.75f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
		{ XMFLOAT3(-4.0f,0.0f,-4.0f),	XMFLOAT2(0.0f ,1.0f),		XMFLOAT4(0.0f,1.0f,0.0f, 0.0f),		XMFLOAT3(1,0,0) },
	};

	WORD indices[] =
	{
		0,1,5,
		1,6,5,
		1,2,6,
		2,7,6,
		2,3,7,
		3,8,7,
		3,4,8,
		4,9,8,

		5,6,10,
		6,11,10,
		6,7,11,
		7,12,11,
		7,8,12,
		8,13,12,
		8,9,13,
		9,14,13,

		10,11,15,
		11,16,15,
		11,12,16,
		12,17,16,
		12,13,17,
		13,18,17,
		13,14,18,
		14,19,18,

		15,16,20,
		16,21,20,
		16,17,21,
		17,22,21,
		17,18,22,
		18,23,22,
		18,19,23,
		19,24,23,
	};


	StaticMeshComponent = ObjLoader::GetInstance()->CreateMesh("planeObj", vert, ind, m*n, triCount*3);
	StaticMeshComponent->load();
	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("GrassTexture.tga"));
	//delete[] ind;
	//delete[] vert;

	ScaleObject(XMVectorSet(1, 1, 1, 1));
}

void PlaneObject::Update(float deltaTime)
{
	TranslateObject(XMVectorSet(2.0f, 2.0f, 2.0f, 1.0f));
	SceneObject::Update(deltaTime);

}

void PlaneObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{

//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);
}