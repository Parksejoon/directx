//
// FileName : color.vs
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
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

//
// Vertex Shader
//
PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	// point로써 표현하기 위해 w = 1.0f로 설정합니다.
	input.position.w = 1.0f;

	// 정점의 위치를 월드, 뷰, 사영의 순서로 계산합니다.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// 픽셀 셰이더에서 사용하기 위해 입력 색상을 저장합니다.
	output.color = input.color;
	
	return output;
}

