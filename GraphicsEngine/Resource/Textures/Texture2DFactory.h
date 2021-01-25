#ifndef _TEXTURE_2D_FACTORY_H_
#define _TEXTURE_2D_FACTORY_H_

#include "../Factories/ResourceFactory.h"
#include "Texture2D.h"

class TEXTURE_2D_FACTORY : public RESOURCE_FACTORY
{
    public:
    static Texture2D* Create(
    FLOAT width,
    FLOAT height,
    uint mipLevels,
    uint arraySize,
    DXGI_FORMAT format,
    DXGI_SAMPLE_DESC sampleDesc,
    D3D11_USAGE usage,
    uint bindFlags,
    uint CPUAccessFlags = 0,
    uint miscFlags = 0
    );

    static Texture2D* Create(char* imageFilePath);
    static Texture2D* Create(Resource* resource);
    
};

#endif //!_TEXTURE_2D_FACTORY_H_