#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_

#include <d3d11.h>

#include "../Resource.h"

class Texture2D : public Resource
{
    friend class TEXTURE_2D_FACTORY;
    ID3D11Texture2D* m_texture;
    DXGI_FORMAT *m_format;
    
public:
    Texture2D(ID3D11Texture2D* texture, DXGI_FORMAT format) 
    :Resource(ResourceType::E_TEXTURE2D), m_texture(texture), m_format(new DXGI_FORMAT(format))
    {}
    Texture2D() : Resource(ResourceType::E_TEXTURE2D){}
    
    ID3D11Texture2D* GetTexture() {return m_texture;}
    DXGI_FORMAT* GetFormat() {return m_format;}
private:
    void SetTexture(ID3D11Texture2D* texture) {m_texture = texture;}
    void SetFormat(DXGI_FORMAT* format) {m_format = format;} 
};

#endif //!_TEXTURE_2D_H_