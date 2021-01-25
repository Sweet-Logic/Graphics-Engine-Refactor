#ifndef _SERIALISEABLE_H_
#define _SERIALISEABLE_H_
#include <sstream>
#include "../JsonUtils.h"
#include "../../Utils/String/StringUtils.h"
#include "../../Resource/Managers/ResourceManager.h"
class Serialiseable
{
public:
	int m_parameterCount = 0;
    virtual JsonUtils::JsonElement* Serialise() = 0;
    virtual void Deserialise(JsonUtils::JsonElement* object) = 0;
};

#endif //!_SERIALISEABLE_H_