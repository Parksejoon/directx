//
// FileName : textureclass.cpp
//
#include "textureclass.h"


//
// CLASS FUCTION
//
TextureClass::TextureClass()
{
	m_texture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;
	ScratchImage image;


	// 텍스쳐를 로드합니다.
	result = LoadFromDDSFile(filename, DDS_FLAGS_NONE, nullptr, image);
	if (FAILED(result))
	{
		// 지금 여기서 버그터짐
		return false;
	}

	result = CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureClass::Shutdown()
{
	// 텍스쳐를 반환합니다.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}