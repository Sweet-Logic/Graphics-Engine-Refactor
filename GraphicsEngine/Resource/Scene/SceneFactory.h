#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_

#include "../Factories/ResourceFactory.h"
#include "Scene.h"

class SCENE_FACTORY : public RESOURCE_FACTORY
{
    public:
    static Scene* Create(char* filePath);

    static Scene* Create(char* sceneName, int sceneID, char* filePath);
    static Scene* Create(Resource* resource);

};

#endif //!_SCENE_FACTORY_H_