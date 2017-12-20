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

	bool Initialize(ID3D11Device*, WCHAR*);					// �ʱ�ȭ
	void Shutdown();										// ����

	ID3D11ShaderResourceView* GetTexture();					// �ؽ��ĸ� �������� �Լ�

private:
	ID3D11ShaderResourceView* m_texture;					// �ؽ���
};


