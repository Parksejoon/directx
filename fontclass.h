//
// FileName : fontclass.h
//
#pragma once


//
// INCLUDES
//
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;


//
// MY CLASS INCLUDES
//
#include "textureclass.h"


//
// Class Name : FontClass
//
class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};
	
public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initiialize(ID3D11Device*, char*, WCHAR*);					// �ʱ�ȭ
	void Shutdown();												// ����

	ID3D11ShaderResourceView* GetTexture();						   // �ؽ��ĸ� ������
	void BuildVertexArray(void*, char*, float, float);			   // ���ڿ��� ���� ���ڸ� �׸� �ﰢ������ �����迭�� ������
																   
private:														   
	bool LoadFontData(char*);									   // ��Ʈ ������ �ҷ���
	void ReleaseFontData();										   // ��Ʈ ������ ����
	bool LoadTexture(ID3D11Device*, WCHAR*);					   // �ؽ��� �ҷ���
	void ReleaseTexture();										   // �ؽ��� ����
																   
private:														 
	FontType * m_Font;											   // ��Ʈ
	TextureClass* m_Texture;									   // �ؽ���
};
