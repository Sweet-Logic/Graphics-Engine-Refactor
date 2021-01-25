#ifndef _MATERIAL_FACTORY_H_
#define _MATERIAL_FACTORY_H_

#include "../Factories/ResourceFactory.h"
#include "Material.h"

typedef unsigned int uint;
class MATERIAL_FACTORY : public RESOURCE_FACTORY
{
    public:
    static Material* Create(
        char* filePath // Reletive to the assets folder
    );
    static Material* Create(Resource* resource);
    
};

#endif //!_MATERIAL_FACTORY_H_