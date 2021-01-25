//#include "LightHelper.fx"
//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

#define NUM_LIGHTS 8

struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float Intensity;
};

struct PointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Att;
	float Intensity;
};

struct SpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Direction;
	float Spot;
	float3 Att;
	float Intensity;
};

struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular; // w = specpower;
	float4 Reflect;
};


cbuffer cbFrame : register(b0)
{
	DirectionalLight gDirLight[NUM_LIGHTS];
	PointLight gPointLight[NUM_LIGHTS];
	SpotLight gSpotLight[NUM_LIGHTS];
	float4 EyePosW;

	matrix View;
	matrix Projection;

	matrix gCameraView;
	matrix gCameraProj;

	float gTime;
	float DirLightCount;
	float PointLightCount;
	float SpotLightCount;
};

cbuffer cbObject  : register(b1)
{
	matrix World;
	Material gMaterial;
	float clipTexture;
	float hasTextureMap;
	float hasNormalMap;
	float hasSpecular;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD0;
	float4 ProjTex : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 color : SV_Target0;
	float4 HDRLight : SV_Target1;
};

Texture2D gAmbientMap : register(t0);
Texture2D gDiffuseMap : register(t1);
Texture2D gSpecularMap : register(t2);
Texture2D gESpecularMap : register(t3);
Texture2D gAlpha : register(t4);
Texture2D gBump : register(t5);
Texture2D gShadowMap : register(t6);


TextureCube gEnviromentMap;
SamplerState Sample1;
SamplerComparisonState ShadowSam;





void CalcDirectionalLight(Material mat, DirectionalLight L, float3 normal, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = -L.Direction;

	ambient = mat.Ambient*L.Ambient;

	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);

		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular * L.Specular;
	}
}

void CalcPointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = L.Position - pos;

	float d = length(lightVec);

	ambient = mat.Ambient * L.Ambient;

	if (d > L.Range)
		return;

	lightVec /= d;



	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular  *L.Specular;
	}

	float att = 1.0f / dot(L.Att, float3(1.0f, d, d*d));




	diffuse *= att;
	ambient *= att;
	spec *= att;
}

void CalcSpotLight(Material mat, SpotLight L, float3 pos, float3 normal, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = L.Position - pos;

	float d = length(lightVec);


	if (d > L.Range)
		return;

	lightVec /= d;

	ambient = mat.Ambient * L.Ambient;


	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular  *L.Specular;
	}
	float spot = pow(max(dot(-lightVec, normalize(L.Direction)), 0.0f), L.Spot);

	
	float att = spot / dot(L.Att, float3(1.0f, d, d*d));


	diffuse *= att;
	ambient *= att;
	spec *= att;
}

float CalcShadowFactor(SamplerComparisonState samShadow, Texture2D shadowMap, float4 shadowPos)
{
	shadowPos.x = 0.5f*shadowPos.x + 0.5;
	shadowPos.y = -0.5f*shadowPos.y + 0.5;

	shadowPos.xyz /= shadowPos.w;

	float depth = shadowPos.z;
	const float dx = SMAP_DX;

	float percentLit = 0.0f;
	const float2 offset[9] =
	{
		float2(-dx, -dx),float2(0.0f, -dx),float2(dx, -dx),
		float2(-dx, 0.0f),float2(0.0f, 0.0f),float2(dx, 0.0f),
		float2(-dx, dx),float2(0.0f, dx),float2(dx, dx),
	};
	float mapDepth = 0.0f;
	//return shadowMap.SampleCmpLevelZero(samShadow, shadowPos.xy + offset[4], depth).r;

	[unroll]
	for(int i = 0; i < 9; i++)
	{
		percentLit += shadowMap.SampleCmpLevelZero(samShadow, shadowPos.xy + offset[i], depth).r;


	}

	return percentLit /= 9.0f;
}

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD0;
	float4 ProjTex : TEXCOORD1;
	float3 Color : COLOR;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD, float4 Normal : NORMAL, float3 Tangent : TANGENT)
{
	PS_INPUT output;

	output.WorldPos = mul(Pos, World);
	output.ProjTex = mul(output.WorldPos, gCameraView);
	output.ProjTex = mul(output.ProjTex, gCameraProj);

	output.Pos = mul(output.WorldPos, View);

	//float rotation = (cos((output.Pos.z)/ 1000)/2);

	//	
	//
	//output.Pos = float4(float3((output.Pos.x*cos(rotation)) + (-(output.Pos.y*sin(rotation))), ((output.Pos.x*sin(rotation)) + (output.Pos.y*cos(rotation))), output.Pos.z), 1.0f);

	output.Pos = mul(output.Pos, Projection);

	output.TexCoords = float2(TexCoords.x, TexCoords.y);

	output.Color = float3(0.7f, 0.7f, 0.7f);

	float4 normal;
	normal.xyz = Normal.xyz;
	normal.w = 0.0f;

	output.Normal = normalize(mul(normal, World));
	output.Tangent = normalize(mul(Tangent, World));

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS(PS_INPUT input) : SV_Target
{
	//Always Normalize the normal 
	float3 normal = normalize(input.Normal.xyz);
	input.Tangent = normalize(input.Tangent);

	//normal = float3( 0.0f,1.0f,0.0f );

	PS_OUTPUT output;
	output.HDRLight = 0.0f;

	float3 toEye = normalize(EyePosW - input.WorldPos);

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A, D, S;
	
	float4 TexColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

	float transparancy = 1.0f;

	
	//Texture Mapping Stuff

	//Get the color of the pixel from the color, to be replaced with texture coords
	if (hasTextureMap == 1)
	{
		TexColor = gDiffuseMap.Sample(Sample1, input.TexCoords);

		if (clipTexture)
		{
			clip(TexColor.a - 0.9f);
		}

	}
	else
	{
		TexColor = float4(input.Color, 1.0f);
	}




	//Normal mapping stuff


	//if it has a normal map
	if (hasNormalMap == 1)
	{
		input.Tangent = normalize(input.Tangent);

		//Make sure tangent is completely orthogonal to normal
		input.Tangent = normalize(input.Tangent - dot(input.Tangent, normal)*normal);

		float3 biTangent = cross(input.Tangent, input.Normal);
		//construct tbn matrix
		float3x3 tbn = float3x3(input.Tangent, biTangent, normal.xyz);

		//load normal map
		float3 normalMap = gBump.Sample(Sample1, input.TexCoords).xyz;

		//change the range of the normals from 0 to 1 -> -1 to 1
		normalMap = (2.0f*normalMap) - 1;

		//move the normals in to tangent space.
		normal = normalize(mul(normalMap, tbn));
	}



	float3 shadow = float3(1.0f, 1.0f, 1.0f);
	shadow[0] = CalcShadowFactor(ShadowSam, gShadowMap, input.ProjTex);

	for (int i = 0; i < DirLightCount; i++)
	{
		CalcDirectionalLight(gMaterial, gDirLight[i], normal, toEye, A, D, S);

		ambient += A;
		diffuse += (D * gDirLight[i].Intensity) * shadow[i];
		spec += (S * gDirLight[i].Intensity)* shadow[i];
	}

	for (int j = 0; j < PointLightCount; j++)
	{
		CalcPointLight(gMaterial, gPointLight[j], input.WorldPos.xyz, normal, toEye, A, D, S);

		ambient += A;
		diffuse +=D* gPointLight[j].Intensity;
		spec += S * gPointLight[j].Intensity;
	}

	for (int k = 0; k < SpotLightCount; k++)
	{
		CalcSpotLight(gMaterial, gSpotLight[k], input.WorldPos.xyz, normal, toEye, A, D, S);

		ambient += A;
		diffuse += D * gSpotLight[k].Intensity;
		spec += S *gSpotLight[k].Intensity;
	}

	float4 litColor = (TexColor *(ambient + diffuse)) + spec;
	output.color = (TexColor *(ambient + diffuse)) + spec;

	[flatten]
	if (litColor.r > 1.0f || litColor.g > 1.0f || litColor.b > 1.0f)
	{
		[flatten]
		if (litColor.r > 1.0f)
		{

			output.HDRLight.r = litColor.r;
		}
		[flatten]
		if (litColor.g > 1.0f)
		{

			output.HDRLight.g = litColor.g;

		}
		[flatten]
		if (litColor.b > 1.0f)
		{

			output.HDRLight.b = litColor.b;

		}
	}




	return output;
}


