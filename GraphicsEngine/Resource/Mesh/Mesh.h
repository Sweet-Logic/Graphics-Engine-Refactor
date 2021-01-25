#ifndef _MESH_H_
#define _MESH_H_

#include <d3d11.h>
#include <DirectXMath.h>

#include "../Materials/Material.h"

using namespace DirectX;

struct VertexData //Colour will be handeled by the constant buffer. tho shouldnt be needed.
{
    XMFLOAT4 position;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
    XMFLOAT3 biTangent;
    XMFLOAT2 texCoord;
};

class Mesh
{
    VertexData** m_rawVertexData;
    unsigned int m_vertexCount = 0;
    unsigned int* m_indexData;
    unsigned int m_indexCount = 0;
    unsigned int m_startIndex = 0;
    int m_startVertex = 0;

    ID3D11Buffer*	_vertexBuffer = nullptr;
	ID3D11Buffer*	_indexBuffer = nullptr;
    unsigned int m_stride;
    unsigned int m_offset;

    Material* m_material;

    public:
    Material* GetMaterial() {return m_material;} //Returns the material

    void SetVertexData(VertexData** rawData, int count) 
    {
        for(unsigned int i = 0; i < m_vertexCount; ++i)
        {
            delete m_rawVertexData[i];
        }
        delete[] m_rawVertexData; 
        m_rawVertexData = rawData;
        m_vertexCount = count;
    }
    void SetIndexData(unsigned int* rawData, int count) {delete[] m_indexData; m_indexData = rawData; m_indexCount = count;}

    unsigned int GetIndexCount() {return m_indexCount;}
    unsigned int GetStartIndex() {return m_startIndex;}
    int GetStartVertex() {return m_startVertex;}

	ID3D11Buffer** GetVertexBuffer() { return &_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return _indexBuffer; }

    unsigned int* GetVertexStride() {return & m_stride;}
    unsigned int* GetVertexOffset() {return & m_offset;}
};

#endif //!_MESH_H_