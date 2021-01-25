#ifndef _RENDERER_COMPONENT_H_
#define _RENDERER_COMPONENT_H_

#include "../../../System/Graphics/ShaderGlobals/ConstantBuffers.h"

#include "../Component.h"
class Mesh;
#include <d3d11.h>
class Renderer : public Component
{
protected:
// Constant buffer
    MainConstants::Object m_objectBuffer;
    bool m_renderWireframe = false;
// DX11 Objects
    D3D11_PRIMITIVE_TOPOLOGY m_topology;
    static ID3D11DeviceContext* m_deviceContextRef;

public:
    static void SetDeviceContext(ID3D11DeviceContext* context) {m_deviceContextRef = context;}

    bool RenderWireframe() {return m_renderWireframe;}
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() {return m_topology;}

    virtual void BindMaterials(Mesh*) = 0;
    virtual MainConstants::Object GetObjectBuffer() {return m_objectBuffer;}

    virtual void Draw() = 0;

	virtual JsonUtils::JsonElement* Serialise() override;
    virtual void Deserialise(JsonUtils::JsonElement* object) override;
};
#endif //!_RENDERER_COMPONENT_H_