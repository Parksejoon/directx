//
// FileName : light.vs
//


//
// GLOBALS
//
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};


//
// TYPEDEFS
//
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};


//
// Vertex Shader
//
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    
    // point�ν� ��Ÿ���� ���� w = 1.0f���� �����մϴ�.
    input.position.w = 1.0f;

	// ����, ��, �翵����� ����Ͽ� ������ �մϴ�.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// �ؽ����� ��ǥ�� �ȼ����̴��� ���� �����صӴϴ�.
    output.tex = input.tex;
    
	// ���� ����� ����Ͽ� �븻 ���͸� �����մϴ�.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // �븻 ���͸� ����ȭ�մϴ�.
    output.normal = normalize(output.normal);

    return output;
}