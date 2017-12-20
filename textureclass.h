//
// FileName : textureclass.h
//
#pragma once


//
// LINKING
//
#pragma comment(lib, "DirectXTex.lib")


//
// INCLUDES
//
#include <d3d11.h>
#include <DirectXTex.h>

using namespace DirectX;


//
// Class Name : TextureClass
//
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, WCHAR*);					// 초기화
	void Shutdown();										// 종료

	ID3D11ShaderResourceView* GetTexture();					// 텍스쳐를 가져오는 함수

private:
	ID3D11ShaderResourceView* m_texture;					// 텍스쳐
};


