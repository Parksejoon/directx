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

	bool Initiialize(ID3D11Device*, char*, WCHAR*);					// 초기화
	void Shutdown();												// 종료

	ID3D11ShaderResourceView* GetTexture();						   // 텍스쳐를 가져옴
	void BuildVertexArray(void*, char*, float, float);			   // 문자열을 통해 글자를 그릴 삼각형들의 정점배열을 가져옴
																   
private:														   
	bool LoadFontData(char*);									   // 폰트 데이터 불러옴
	void ReleaseFontData();										   // 폰트 데이터 해제
	bool LoadTexture(ID3D11Device*, WCHAR*);					   // 텍스쳐 불러옴
	void ReleaseTexture();										   // 텍스쳐 해제
																   
private:														 
	FontType * m_Font;											   // 폰트
	TextureClass* m_Texture;									   // 텍스쳐
};
