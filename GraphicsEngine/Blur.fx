//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float2 ScreenSize;
	float gTime;
	float BlurStrength;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float2 TexCoords : TEXCOORD0;
	float2 TexelOffset : TEXELOFFSET;
};

Texture2D gRenderView : register(t0);
SamplerState Sample1;


uniform float2 TexelSize;
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD)
{
	VS_OUTPUT output;
	//Pos.x *= 0.5f;
	float2 texelSize = float2(1.0f/ (ScreenSize.x/1.0f), 1.0f / (ScreenSize.y/1.0f));

	output.Pos = Pos;
	output.TexCoords = TexCoords;
	output.TexelOffset = texelSize;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	//float3 AvaragePixelColor = gRenderView.Sample(Sample1, input.TexCoords);
	float4 color;
	
	

	float weight0;
	float weight1;
	float weight2;
	float weight3;
	float weight4;

	float2 texeloffset = input.TexelOffset;

	//float center = BlurStrength + 1.0f;

	/*color += gRenderView.Sample(Sample1, input.TexCoords) * 0.4;

	for (float x = 1; x <= BlurStrength; x++)
	{
		color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x*x, 0.0f))*weight1;
		color += gRenderView.Sample(Sample1, input.TexCoords + float2((input.TexelOffset.x*x)*-1, 0.0f))*weight1;

		color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f, input.TexelOffset.y*y))*weight1;
		color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f, (input.TexelOffset.y*y)*-1))*weight1;
		for (float y = 0 ; y <= BlurStrength; y++)
		{
			color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x*x, input.TexelOffset.y*y))*weight1;
			color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x*x, (input.TexelOffset.y*y)*-1)))*weight1;

			color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x*x)*-1, input.TexelOffset.y*y))*weight1;
			color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x*x)*-1, (input.TexelOffset.y*y)*-1)))*weight1;
		}
	}*/

	

	weight1 = 0.15;
	weight2 = 0.1;

	color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	color += gRenderView.Sample(Sample1, input.TexCoords) * 0.150342f;

	color += gRenderView.Sample(Sample1, input.TexCoords +	float2(	input.TexelOffset.x, 0.0f))*0.094907;
	color += gRenderView.Sample(Sample1, input.TexCoords +	float2(	0.0f, input.TexelOffset.y))*0.094907;
	color += gRenderView.Sample(Sample1, input.TexCoords +	float2(-input.TexelOffset.x, 0.0f))*0.094907;
	color += gRenderView.Sample(Sample1, input.TexCoords +	float2(	0.0f,-input.TexelOffset.y))*0.094907;

	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, input.TexelOffset.y))*  	0.059912f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, -input.TexelOffset.y))*  0.059912f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, -input.TexelOffset.y))*	0.059912f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, input.TexelOffset.y))*	0.059912f;

	input.TexelOffset += texeloffset;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2( input.TexelOffset.x, 0.0f))*	0.023792f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2( 0.0f, input.TexelOffset.y))*	0.023792f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, 0.0f))*	0.023792f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2( 0.0f,-input.TexelOffset.y))*	0.023792f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, input.TexelOffset.y))*  0.003765f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, -input.TexelOffset.y))*  0.003765f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, -input.TexelOffset.y))*0.003765f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, input.TexelOffset.y))*0.003765f;

	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, 0.0f+ texeloffset.y))*  0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f+ texeloffset.x, input.TexelOffset.y))*  0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, 0.0f- texeloffset.y))* 0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f-texeloffset.x, -input.TexelOffset.y))*  0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(input.TexelOffset.x, 0.0f - texeloffset.y))* 0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f - texeloffset.x, input.TexelOffset.y))* 0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(-input.TexelOffset.x, 0.0f + texeloffset.y))*0.015019f;
	color += gRenderView.Sample(Sample1, input.TexCoords + float2(0.0f + texeloffset.x, -input.TexelOffset.y))*0.015019f;




	//color /= 3.0f;

	color.a = 1.0f;

	return  color;
}
