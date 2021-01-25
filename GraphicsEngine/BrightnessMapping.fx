//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

struct Light
{
	float3 dir;
	float pad1;
	float3 pos;
	float range;
	float3 att;
	float specularPower;
	float4 ambient;
	float4 diffuse;
	float4 specular;
};

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float hasNormalMap;
};

cbuffer ConstBuffPerFrame
{
	Light light;
	float4 EyePosW;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD;
};

Texture2D gNormalMap;
SamplerState Sample1;


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD, float4 Normal : NORMAL, float3 Tangent : TANGENT)
{

	VS_OUTPUT output;

	output.WorldPos = mul(Pos, World);
	output.Pos = mul(output.WorldPos, View);
	output.Pos = mul(output.Pos, Projection);



	output.TexCoords = float2(TexCoords.x, TexCoords.y);

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
float4 PS(VS_OUTPUT input) : SV_Target
{
	//Always Normalize the normal 
	float3 normal = normalize(input.Normal.xyz);
	input.Tangent = normalize(input.Tangent);
	input.Normal = normalize(input.Normal);
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
		float3 normalMap = gNormalMap.Sample(Sample1, input.TexCoords).xyz;

		//change the range of the normals from 0 to 1 -> -1 to 1
		normalMap = (2.0f*normalMap) - 1;

		//move the normals in to tangent space.
		normal = normalize(mul(normalMap, tbn));

	}



	//Lighting Stuff

	//Initialize the final color
	float3 finalColor = float3(0.0f,0.0f,0.0f);

	//Initialize a vector that points from the pixel in world space to the lights position
	float4 vToLight = float4(light.pos.xyz - input.WorldPos.xyz, 0.0f);

	//Get the magnatude of the vector to the light
	float distance = length(vToLight);

	//Calculate the ambient color of the pixel

	float canSeeLight = dot(vToLight, float3(input.Normal.xyz));



	//Check to see if the pixel is too far from the light
	if (distance > light.range || canSeeLight < 0.0f)
	{
		//If the pixel is too far use the ambient color
		return float4(0.0f,0.0f,0.0f,1.0f);
	}

	//Convert the vector to the light in to a unit vector
	vToLight /= distance;


	//Get the angle between the light and the normal of the pixel
	float howMuchLight = dot(vToLight,normal);

	//if the angle between the light and the pixel normal is positive then the light can see the pixel
	if (howMuchLight > 0.7f)
	{
		//The angle between the light and the pixel normal acts as the intensity of the light
		// this is then multiplied with the diffuse of the light and of the color of the pixel
		// to get the color
		finalColor = howMuchLight * light.diffuse.xyz;

		//Calculate the fall off of the light
		//					Constant		Linear					Exponential
		float Attenuation = light.att.x + (light.att.y*distance) + (light.att.z * (distance * distance));

		//If the attenuation is 0 then there is no fall off of the light
		if (Attenuation != 0)
		{
			finalColor.xyz /= Attenuation;
		}

	}
	else
	{
		//If the pixel is too far use the ambient color
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float3 toEye = normalize(EyePosW - input.WorldPos.xyz);

	float3 surfacetoLight = normalize(light.pos.xyz - input.WorldPos.xyz);

	float3 reflection = reflect(-surfacetoLight, normal.xyz);

	float specAmount = pow(max(dot(reflection, toEye), 0.0f), light.specularPower);

	float3 specular = specAmount * (/**add material spec here **/light.specular).rgb;

	// clamp the value of the final color and the ambient between the ranges of 0 and 1
	finalColor = finalColor + light.ambient + specular;

	// return the final color of the pixel and its alpha
	return float4(finalColor, 1.0f);
}