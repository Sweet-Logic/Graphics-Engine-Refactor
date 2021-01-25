#include "ObjLoader.h"
#include <fstream>
#include <string>
#include "MaterialLibaryLoader.h"

ObjLoader::ObjLoader()
{
}


ObjLoader* ObjLoader::_instance = nullptr;
std::vector<Object*> ObjLoader::LoadedObjects;
ID3D11Device* ObjLoader::_device = nullptr;


MeshComponent * ObjLoader::LoadMeshFromFile(std::string filepath)
{


	MeshComponent* Output;

	Output = new MeshComponent();
	Output->MatLib = new Libary;

	 int VertexCount = 0;
	 int FaceCount = 0;
	 int GroupCount = 0;
	std::string ObjectName;
	std::vector<XMFLOAT3> _inVerticies;
	std::vector<XMFLOAT3> _inNormals;
	std::vector<XMFLOAT3> _inTexCoords;
	std::vector<Group> _inGroups;

	std::vector<std::vector<WORD>> _inIndices;

	std::vector<Processed> _prossessedVertes;

	std::vector<Vertex> _outVertex;

	FileInput FileData;

	std::ifstream inFile("Models/" + filepath, std::ifstream::in);
	GroupCount = 0;
	std::string textReadIn;
	std::vector<WORD> indiciesRead;
	while (std::getline(inFile, textReadIn))
	{
		int offset = 3;
		if (textReadIn.find("object", 2) != -1)
		{
			ObjectName = textReadIn.substr(9, textReadIn.length() - 10);
		}
		else if (textReadIn.find("mtllib", 0) != -1)
		{
			std::string temp = textReadIn.substr(7, textReadIn.length());
			Output->MatLib = MaterialLibaryLoader::GetInstance()->LoadMtl(temp);
		}
		else if (textReadIn.find("usemtl", 0) != -1)
		{
			std::string temp = textReadIn.substr(7, textReadIn.length());
			_inGroups.at(GroupCount-1).mat = MaterialLibaryLoader::GetInstance()->GetMaterial(temp, Output->MatLib);
		}
		else if (textReadIn[0] == 'v')
		{
			std::string vString;
			float vOut[3];
			
			for (int i = 0; i < 3; i++)
			{
				int end = textReadIn.find(' ', (offset + 1)) - offset;

				if (end < 0) { end = textReadIn.length() - 1; }

				vString = textReadIn.substr(offset, end);

				vOut[i] = stof(vString);
				offset += end;
			}
			XMFLOAT3 constructedPoint = XMFLOAT3(vOut[0], vOut[1], vOut[2]);

			if (textReadIn[1] == ' ')
			{
				VertexCount++;
				_inVerticies.push_back(constructedPoint);
			}
			else if (textReadIn[1] == 'n')
			{
				_inNormals.push_back(constructedPoint);
			}
			else if (textReadIn[1] == 't')
			{
				_inTexCoords.push_back(XMFLOAT3(constructedPoint.x, 1-constructedPoint.y, constructedPoint.z));
			}
			
		}
		else if (textReadIn[0] == 'g')
		{
			_inGroups.push_back(Group());
			_inIndices.push_back(indiciesRead);
			indiciesRead.clear();
			GroupCount++;
		}

		else if (textReadIn.find("f ", 0) != -1)
		{
			int indicies = 0;
			offset = textReadIn.find(" ", 0);
			int face[3];
			for (int i = 0; i < 3; i++)
			{
				
				Vertex Out;
				
				for (int j = 0; j < 3; j++)
				{
					int slash = (textReadIn.find('/', (offset + 1)));
					int space = (textReadIn.find(' ', (offset + 1)));
					int end = (slash > space) ? space : slash;

					if (end < 0) { end = textReadIn.length() - 1; }

					face[j] = stoi(textReadIn.substr(offset, end));

					offset = end+1;

					
				}

				bool created = false;
				int pos = 0;
				for (std::vector<Processed>::size_type k = 0; k < _prossessedVertes.size(); k++)
				{
					if (_prossessedVertes.at(k).vert == face[0] && _prossessedVertes.at(k).Tex == face[1] && _prossessedVertes.at(k).normal == face[2])
					{
						created = true;
						_inIndices.at(GroupCount-1).push_back(k);
						pos = k;
						break;
					}
					else
					{

						created = false;
					}
				}

				if (!created)
				{
					_inIndices.at(GroupCount - 1).push_back(_prossessedVertes.size());
					

					Out.Pos = _inVerticies[face[0] - 1];
					Out.TexCoords = XMFLOAT2(_inTexCoords[face[1] - 1].x, _inTexCoords[face[1] - 1].y);
					Out.Normal = XMFLOAT4(_inNormals[face[2] - 1].x, _inNormals[face[2] - 1].y, _inNormals[face[2] - 1].z, 0.0f);

					_prossessedVertes.push_back(Processed(face[0], face[2], face[1], _outVertex.size()));
					_outVertex.push_back(Out);
				}
				
			}
			FaceCount++;
		}
		

	}

	FileData.Verticies = new Vertex[_outVertex.size()];
	FileData.Indicies = new WORD*[GroupCount];
	FileData.GroupIndicies = new int[GroupCount];

	
	for ( int i = 0; i < GroupCount; i++)
	{
		FileData.Indicies[i] = new WORD[FaceCount * 3];
		int Count = 0;
		for ( int j = 0; j < FaceCount * 3; j++)
		{
			// indices
			FileData.Indicies[i][j] = _inIndices.at(i).at(j);
			Count++;
		}
		FileData.GroupIndicies[i] = Count;
	}

	FileData.TotalSmoothingGroups = GroupCount;

	Output->meshGroups = new Group[GroupCount];

	//moves the indexs 
	for (std::vector<Vertex>::size_type i = 0; i < _outVertex.size(); i++)
	{
		FileData.Verticies[i].Pos = _outVertex.at(i).Pos;
		FileData.Verticies[i].Normal = _outVertex.at(i).Normal;
		FileData.Verticies[i].TexCoords = _outVertex.at(i).TexCoords;
		FileData.Verticies[i].Tangent = _outVertex.at(i).Tangent;

	}


	//Output->GroupIndicies = new int[GroupCount];

	//Maps = new Texture2D**[GroupCount];
	int offset = 0;
	for ( int i = 0; i < GroupCount; i++)
	{
		
		Output->meshGroups[i].startIndex = offset;
		Output->meshGroups[i].indexCount = FileData.GroupIndicies[i];
		Output->meshGroups[i].mat = _inGroups.at(i).mat;

		//Output->Maps[i] = new Texture2D*[3];
		//Output->GroupIndicies[i] = FileData.GroupIndicies[i];

		offset += FileData.GroupIndicies[i];
	}

	int* indexArray = new int[offset];

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * _outVertex.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = FileData.Verticies;

	HRESULT hr;

	hr = _device->CreateBuffer(&bd, &InitData, Output->GetVertexBuffer());

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * FaceCount * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = FileData.Indicies[0];


	hr = _device->CreateBuffer(&bd, &InitData, Output->GetIndexBuffer());

	Output->Groups = GroupCount;
	
	LoadedObjects.push_back(new Object(ObjectName, Output));

	return Output;
}

MeshComponent * ObjLoader::CreateMesh(std::string meshName, Vertex VertexData[], WORD indexData[], int vertexCount, int indexCount)
{
	MeshComponent* Output = new MeshComponent();
	Output->MatLib = new Libary;

	for (int i = 0; i < (indexCount/3); i++)
	{
		/////Normals

		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);
		////Get the vector describing one edge of our triangle (edge 0,2)
		float vecX = VertexData[indexData[(i * 3)]].Pos.x - VertexData[indexData[(i * 3) + 2]].Pos.x;
		float vecY = VertexData[indexData[(i * 3)]].Pos.y - VertexData[indexData[(i * 3) + 2]].Pos.y;
		float vecZ = VertexData[indexData[(i * 3)]].Pos.z - VertexData[indexData[(i * 3) + 2]].Pos.z;
		XMVECTOR edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our first edge

																 //Get the vector describing another edge of our triangle (edge 2,1)
		vecX = VertexData[indexData[(i * 3) + 2]].Pos.x - VertexData[indexData[(i * 3) + 1]].Pos.x;
		vecY = VertexData[indexData[(i * 3) + 2]].Pos.y - VertexData[indexData[(i * 3) + 1]].Pos.y;
		vecZ = VertexData[indexData[(i * 3) + 2]].Pos.z - VertexData[indexData[(i * 3) + 1]].Pos.z;
		XMVECTOR edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our second edge


																 //Cross multiply the two edge vectors to get the un-normalized face normal
		XMStoreFloat3(&unnormalized, XMVector3Cross(edge2, edge1));

		VertexData[indexData[(i * 3) + 0]].Normal = XMFLOAT4(unnormalized.x, unnormalized.y, unnormalized.z, 0.0f);
		VertexData[indexData[(i * 3) + 1]].Normal = XMFLOAT4(unnormalized.x, unnormalized.y, unnormalized.z, 0.0f);
		VertexData[indexData[(i * 3) + 2]].Normal = XMFLOAT4(unnormalized.x, unnormalized.y, unnormalized.z, 0.0f);

		////TANGENT

		//Find first texture coordinate edge 2d vector
		float tcU1 = VertexData[indexData[(i * 3)]].TexCoords.x - VertexData[indexData[(i * 3) + 2]].TexCoords.x;
		float tcV1 = VertexData[indexData[(i * 3)]].TexCoords.y - VertexData[indexData[(i * 3) + 2]].TexCoords.y;

		//Find second texture coordinate edge 2d vector
		float tcU2 = VertexData[indexData[(i * 3) + 2]].TexCoords.x - VertexData[indexData[(i * 3) + 1]].TexCoords.x;
		float tcV2 = VertexData[indexData[(i * 3) + 2]].TexCoords.y - VertexData[indexData[(i * 3) + 1]].TexCoords.y;


		XMFLOAT3 tangent;
		//Find tangent using both tex coord edges and position edges
		tangent.x = (tcV1 * XMVectorGetX(edge1) - tcV2 * XMVectorGetX(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
		tangent.y = (tcV1 * XMVectorGetY(edge1) - tcV2 * XMVectorGetY(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
		tangent.z = (tcV1 * XMVectorGetZ(edge1) - tcV2 * XMVectorGetZ(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));

		VertexData[indexData[(i * 3) + 0]].Tangent = tangent;
		VertexData[indexData[(i * 3) + 1]].Tangent = tangent;
		VertexData[indexData[(i * 3) + 2]].Tangent = tangent;
	}



	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = VertexData;

	HRESULT hr = _device->CreateBuffer(&bd, &InitData, Output->GetVertexBuffer());


	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexData;


	hr = _device->CreateBuffer(&bd, &InitData, Output->GetIndexBuffer());

	Output->Groups = 1;
	Output->meshGroups = new Group[1]{Group()};
	Output->meshGroups[0].indexCount = indexCount;
	Output->meshGroups[0].startIndex = 0;
	Output->meshGroups[0].mat = nullptr;


	LoadedObjects.push_back(new Object(meshName, Output));

	return Output;
}
