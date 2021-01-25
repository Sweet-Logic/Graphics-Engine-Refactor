#ifndef _SHADER_RESOURCE_VIEW_H_
#define _SHADER_RESOURCE_VIEW_H_

#include "../../../../Resource/Textures/Texture2D.h"


class ShaderResourceView
{
	ID3D11ShaderResourceView* m_resourceView;

    public:
    ShaderResourceView(Texture2D*);
    void Release();
    ID3D11ShaderResourceView* GetShaderResourceView() {return m_resourceView;}
};

#endif //!_SHADER_RESOURCE_VIEW_H_