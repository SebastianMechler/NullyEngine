//cbuffer PerApplication : register(b0)
//{
//	matrix projectionMatrix;
//}
//
//cbuffer PerFrame : register(b1)
//{
//	matrix viewMatrix;
//}
//
//cbuffer PerObject : register(b2)
//{
//	matrix worldMatrix;
//}

struct VS_IN
{
	float3 position : POSITION;
	float3 color	: COLOR;
};

struct PS_IN
{
	float4 color	: COLOR;
	float4 position : SV_POSITION;
};

PS_IN VS_Main(VS_IN input)
{
	PS_IN output;

	//matrix mvp = mul(projectionMatrix, mul(viewMatrix, worldMatrix));
	//output.position = mul(mvp, float4(input.position, 1.0f));
	output.position = float4(input.position, 1.0f);
	output.color = float4(input.color, 1.0f);

	return output;
}

float4 PS_Main(PS_IN input) : SV_TARGET
{
	return input.color;
}