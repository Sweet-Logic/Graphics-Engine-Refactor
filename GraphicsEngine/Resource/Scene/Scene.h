#ifndef _SCENE_H_
#define _SCENE_H_
#include "../../Resource/Resource.h"

struct Scene : public Resource
{
	friend class SCENE_FACTORY;
	Scene() : Resource(ResourceType::E_SCENE) {}
    bool m_isDirty = true;
	unsigned int m_sceneID;
    void SetDirty(bool dirty) {m_isDirty = dirty;}
    int GetSceneID() {return m_sceneID;}
public:
    bool GetDirty() {return m_isDirty;}

    void SetSceneID(int sceneid) {m_sceneID = sceneid;}
};

#endif //!_SCENE_H_