
SamplerState samLinear : register(s0);

cbuffer cbNeverChanges : register( b0 )
{
    matrix View;
};

cbuffer cbChangeOnResize : register( b1 )
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame : register( b2 )
{
    matrix World;
    float4 vMeshColor;
};


struct VS_INPUT
{
    float4 Pos : POSITION;
	float3 Color : COLOR;
	float4 Data : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 Data : TEXCOORD0;
};


PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( float4(input.Pos.xyz, 1.0), World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

	output.Color = input.Color;
	output.Data = input.Data;

    return output;
}

float4 PS( PS_INPUT input) : SV_Target
{

	return float4(input.Color, 1.0);
}
