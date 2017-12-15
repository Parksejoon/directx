//
// FileName : texture.vs
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
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


//
// Vertex Shader
//
PixelInputType TextureVertexShader(VertexInputType input)
{
    PixelInputType output;


    // point로써 표현하기 위해 w = 1.0f로 설정합니다.
    input.position.w = 1.0f;

    // 월드, 뷰, 사영 행렬을 사용하여 정점의 위치를 연산합니다.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // 출력 데이터를 대입합니다.
    output.tex = input.tex;

    return output;
}
