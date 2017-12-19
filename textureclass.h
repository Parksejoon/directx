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

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};


