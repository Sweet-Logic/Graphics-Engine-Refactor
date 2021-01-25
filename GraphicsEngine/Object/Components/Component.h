#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "../GameObject/GameObject.h"
#include "../../File_IO/Serialising/Serialiseable.h"

class Component : public Serialiseable
{
public:
    virtual char* GetName() = 0;
    GameObject* GetGameObject() {return m_gameObject;}
    
	virtual JsonUtils::JsonElement* Serialise() override = 0;
    virtual void Deserialise(JsonUtils::JsonElement* object) override = 0;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void PostUpdate() = 0;

	void SetGameObject(GameObject* gameObject) { m_gameObject = gameObject; }
protected:
    GameObject* m_gameObject; //Referance to the owning object of this component

};

#endif //!_COMPONENT_H_