#ifndef _STATIC_MESH_H_
#define _STATIC_MESH_H_

#include "../Resource.h"
#include "Mesh.h"



class StaticMesh : public Resource
{
    friend class STATIC_MESH_FACTORY;
    public:
    StaticMesh() : Resource(ResourceType::E_STATIC_MESH){}
    Mesh** m_elements;
    unsigned int m_elementCount;
}; 

#endif //!_STATIC_MESH_H_