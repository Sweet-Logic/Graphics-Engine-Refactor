#ifndef _OBJ_READER_H_
#define _OBJ_READER_H_
#include "../FileReader.h"
#include "../../../Resource/Mesh/Mesh.h"
#include <d3d11.h>
#include <vector>
#include <iostream>
#include <sstream>

//Not a perfect tga reader as it only supports colour mapped images at 32 bits.

using namespace DirectX;
struct OBJ_Info : FileInfo
{
	uint meshCount;
	Mesh** meshs;
};

class OBJ_READER : public FileReader<OBJ_READER>
{
	public:
	static XMFLOAT3 GetVector(char* str);
};

bool FileReader<OBJ_READER>::CheckExtention(char* extention)
{
    return StrUtils::Compare(extention, ".obj");
}

XMFLOAT3 OBJ_READER::GetVector(char* str)
{
	int length = StrUtils::GetLength(str);
	int start = 3;
	int space = StrUtils::Find(str, ' ', start);
	char* vector = StrUtils::copy(str, start, length - start);
	
	std::stringstream ss(vector);
	XMFLOAT3 value;
	ss >> value.x;
	ss >> value.y;
	ss >> value.z;	
	return value;
}


FileInfo* FileReader<OBJ_READER>::ReadFile(char* filePath)
{
    OBJ_Info* fileInfo = new OBJ_Info();

	std::ifstream file(filePath, std::ifstream::in);
	std::vector<XMFLOAT3> vertex;
	std::vector<XMFLOAT3> texCoords;
	std::vector<XMFLOAT3> normals;
	std::vector<XMFLOAT3> *current;
	
	std::vector<Mesh> meshes;
	meshes.push_back(Mesh());
	int currentMesh = 0;

	char buffer[255];
	while (file.getline(buffer, 255))
	{
		switch(buffer[0])
		{
			case ' ':
			{

			}
			case '#'://Comment
			{

			}
			case 'm'://definition of a material libary path or merging group
			{
				
			}
			case 'v'://relating to a vertex
			{
				//number
				if(buffer[1] == ' ')
				{//vertex	
					current = &vertex;
					vertex.push_back(OBJ_READER::GetVector(buffer));
				}
				else if(buffer[1] == 't')
				{//texcoord
					current = &texCoords;
					texCoords.push_back(OBJ_READER::GetVector(buffer));
				}
				else if(buffer[1] == 'n')
				{//normals
					current = &normals;
				}

				do{
					current->push_back(OBJ_READER::GetVector(buffer));
				}while (file.getline(buffer, 255) && buffer[0] == 'v');
			}
			case 'p'://point
			{

			}
			case 'o'://Object Name
			{

			}
			case 'g'://group within the object
			{

			}
			case 's': //shading group or shadow casting
			{

			}
			case 'u'://start of use material
			{

			}
			case 'l': //start of lod?
			{

			}
			case 't'://start of trace
			{

			}
			case 'f'://face
			{
				int vertIndex = 0;
				int texIndex = 0;
				int normIndex = 0;

				std::vector<VertexData*> vertData;
				std::vector<unsigned int> intData;
				
				std::stringstream ss;
				int j = 0;
				do{
					ss.str(StrUtils::copy(buffer, 2, StrUtils::GetLength(buffer) -2));
					
					VertexData* newVert = new VertexData();
					ss >> vertIndex >> texIndex >> normIndex;
					newVert->position = XMFLOAT4(vertex[vertIndex-1].x, vertex[vertIndex-1].y, vertex[vertIndex-1].z, 1.0f);
					newVert->normal = normals[normIndex-1];
					newVert->tangent = XMFLOAT3();
					newVert->biTangent = XMFLOAT3();
					newVert->texCoord = XMFLOAT2(texCoords[texIndex-1].x, texCoords[texIndex-1].y);
					intData.push_back(j++);
					vertData.push_back(newVert);
					
					newVert = new VertexData();
					ss >> vertIndex >> texIndex >> normIndex;
					newVert->position = XMFLOAT4(vertex[vertIndex-1].x, vertex[vertIndex-1].y, vertex[vertIndex-1].z, 1.0f);
					newVert->normal = normals[normIndex-1];
					newVert->tangent = XMFLOAT3();
					newVert->biTangent = XMFLOAT3();
					newVert->texCoord = XMFLOAT2(texCoords[texIndex-1].x, texCoords[texIndex-1].y);
					intData.push_back(j++);
					vertData.push_back(newVert);

					newVert = new VertexData();
					ss >> vertIndex >> texIndex >> normIndex;
					newVert->position = XMFLOAT4(vertex[vertIndex-1].x, vertex[vertIndex-1].y, vertex[vertIndex-1].z, 1.0f);
					newVert->normal = normals[normIndex-1];
					newVert->texCoord = XMFLOAT2(texCoords[texIndex-1].x, texCoords[texIndex-1].y);
					intData.push_back(j++);
					vertData.push_back(newVert);

					////Get the vector describing one edge of our triangle (edge 0,2)
					XMVECTOR vv0 = XMLoadFloat4(&vertData[vertData.size()-3]->position);
					XMVECTOR vv1 = XMLoadFloat4(&vertData[vertData.size()-2]->position);
					XMVECTOR vv2 = XMLoadFloat4(&vertData[vertData.size()-1]->position);

					XMVECTOR P = vv1 - vv0;
					XMVECTOR Q = vv2 - vv0;

					float tcU1 = vertData[vertData.size()-2]->texCoord.x - vertData[vertData.size()-3]->texCoord.x;
					float tcV1 = vertData[vertData.size()-2]->texCoord.y - vertData[vertData.size()-3]->texCoord.y;
					float tcU2 = vertData[vertData.size()-1]->texCoord.x - vertData[vertData.size()-3]->texCoord.x;
					float tcV2 = vertData[vertData.size()-1]->texCoord.y - vertData[vertData.size()-3]->texCoord.y;

					float tmp = 0.0f;
					float val = tcU1*tcV2 - tcU2*tcV1;
					if (fabsf(val) <= 0.0001f)
					{
						tmp = 1.0f;
					}
					else
					{
						tmp = 1.0f / (val);
					}

					XMFLOAT3 PF3, QF3;
					XMStoreFloat3(&PF3, P);
					XMStoreFloat3(&QF3, Q);

					XMFLOAT3 tangent;
					tangent.x = (tcV2*PF3.x - tcV1*QF3.x);
					tangent.y = (tcV2*PF3.y - tcV1*QF3.y);
					tangent.z = (tcV2*PF3.z - tcV1*QF3.z);

					tangent.x = tangent.x*tmp;
					tangent.y = tangent.y*tmp;
					tangent.z = tangent.z*tmp;

					XMVECTOR vt = XMLoadFloat3(&tangent);
					XMVECTOR vn = XMLoadFloat3(&newVert->normal);
					// left hand system b = t cross n (rh would be b = n cross t)
					XMVECTOR vb = XMVector3Cross(vt, vn);
					vt = XMVector3Normalize(vt);
					vb = XMVector3Normalize(vb);

					XMStoreFloat3(&vertData[vertData.size()-3]->tangent, vt);
					XMStoreFloat3(&vertData[vertData.size()-2]->tangent, vt);
					XMStoreFloat3(&vertData[vertData.size()-1]->tangent, vt);
					XMStoreFloat3(&vertData[vertData.size()-3]->biTangent, vb);
					XMStoreFloat3(&vertData[vertData.size()-2]->biTangent, vb);
					XMStoreFloat3(&vertData[vertData.size()-1]->biTangent, vb);
					
				}while (file.getline(buffer, 255) && buffer[0] == 'f');
				
				VertexData** rawData = new VertexData*[vertData.size()];
				unsigned int* indexData = new unsigned int[intData.size()];
				int i = -1;
				while (vertData.size() > ++i && (rawData[i] = vertData[i]));
				i = -1;
				while (intData.size() > ++i && (indexData[i] = intData[i]));

				meshes[currentMesh].SetVertexData(rawData, vertData.size());
				meshes[currentMesh].SetIndexData(indexData, intData.size());
				vertData.clear();

				meshes.push_back(Mesh());
				int currentMesh = 0;
			}
		}
	}
	
    return fileInfo;
}

#endif //!_OBJ_READER_H_