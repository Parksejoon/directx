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
cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
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
    float3 viewDirection : TEXCOORD1;
};


//
// Vertex Shader
//
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;

    
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

    // ���� �ȿ� ������ ��ǥ�� ����մϴ�.
    worldPosition = mul(input.position, worldMatrix);

    // ī�޶� �ٶ󺸴� ������ ���մϴ�.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

    // ��� ����� ī�޶��� ������ ����ȭ�մϴ�.
    output.viewDirection = normalize(output.viewDirection);

    return output;
}