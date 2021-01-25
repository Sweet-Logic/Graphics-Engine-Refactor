#ifndef _STATIC_MESH_FACTORY_H_
#define _STATIC_MESH_FACTORY_H_

#include "../Factories/ResourceFactory.h"
#include "StaticMesh.h"

typedef unsigned int uint;
class STATIC_MESH_FACTORY : public RESOURCE_FACTORY
{
    public:
    static StaticMesh* Create(char* filePath);
    static StaticMesh* Create(VertexData* m_vertexData, uint* m_indicies);
    static StaticMesh* Create(Resource* resource);
    
};

#endif //!_STATIC_MESH_FACTORY_H_