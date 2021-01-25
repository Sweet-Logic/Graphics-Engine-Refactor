//Stores the neccicary information to render the mesh!
#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "RendererComponent.h"
#include "../../../Resource/Mesh/StaticMesh.h"

struct MeshRenderer : public Renderer
{  
    class Groups
    {
        //vertex Data
        //Indacies
        //Maps
    };

    StaticMesh* m_staticMesh = nullptr;

    virtual char* GetName() override;
    virtual void BindMaterials(Mesh*);
    virtual void BindBuffers(Mesh*) ;
    virtual MainConstants::Object GetObjectBuffer()override;
    virtual void Draw()override;
	virtual JsonUtils::JsonElement* Serialise() override;
    virtual void Deserialise(JsonUtils::JsonElement* object) override;
};

#endif //!_MESH_RENDERER_H_