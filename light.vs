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

    
    // point로써 나타내기 위해 w = 1.0f으로 설정합니다.
    input.position.w = 1.0f;

	// 월드, 뷰, 사영행렬을 사용하여 연산을 합니다.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// 텍스쳐의 좌표를 픽셀셰이더를 위해 저장해둡니다.
    output.tex = input.tex;
    
	// 월드 행렬을 사용하여 노말 벡터를 연산합니다.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // 노말 벡터를 정규화합니다.
    output.normal = normalize(output.normal);

    // 월드 안에 정점의 좌표를 계산합니다.
    worldPosition = mul(input.position, worldMatrix);

    // 카메라가 바라보는 방향을 구합니다.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

    // 방금 계산한 카메라의 방향을 정규화합니다.
    output.viewDirection = normalize(output.viewDirection);

    return output;
}