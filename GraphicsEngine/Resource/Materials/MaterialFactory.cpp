#include "MaterialFactory.h"

Material* MATERIAL_FACTORY::Create(char* filePath)
{
	return nullptr;
}

Material* MATERIAL_FACTORY::Create(Resource* resource)
{
    Material* mat = static_cast<Material*>(resource);
	return mat;
}