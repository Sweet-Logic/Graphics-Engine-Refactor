#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../Resource.h"
#include "../../System/Graphics/Views/ShaderResourceViews/ShaderResourceView.h"


class Material : public Resource
{
public:
	enum MaterialFlag
	{
		NO_MATERIAL = 0,
		AMBIENT_MAP = 0x00000001, // 1
		DIFFUSE_MAP = 0x00000002, // 2
		SPECULAR_MAP = 0x00000004, // 4
		SPECULAR_PWR_MAP = 0x00000008, // 8
		ALPHA_MAP = 0x00000010, // 16
		NORMAL_MAP = 0x00000020, // 32
		HEIGHT_MAP = 0x00000040, // 64  
	};

	enum MaterialIndex
	{
		INDEX_OBJECT_AMBIENT_MAP = 0,
		INDEX_OBJECT_DIFFUSE_MAP,
		INDEX_OBJECT_SPECULAR_MAP,
		INDEX_OBJECT_SPECULAR_PWR_MAP,
		INDEX_OBJECT_ALPHA_MAP,
		INDEX_OBJECT_NORMAL_MAP,
		INDEX_OBJECT_HEIGHT_MAP,
		INDEX_COUNT
	};

	friend class MATERIAL_FACTORY;
	Material() : Resource(ResourceType::E_BASIC_MATERIAL) {};
	float Ns; //Specular Exponent
	float Ni;
	float d; //disolved -- The transparancy 1.0 = opaque. but not depenent on the thickness of the material
	float Tr; //disolved (inverted: Tr = 1 - d) if d = 0.3, Tr = 0.7
	float Tf[3];
	int illum; //Illumination Model
	float Ka[3]; //Diffuse Colour
	float Kd[3]; //Ambient Colour
	float Ks[3]; //Specular Colour
	float Ke[3]; 
    ShaderResourceView* m_materialMaps[MaterialIndex::INDEX_COUNT];
};

#endif //!_MATERIAL_H_