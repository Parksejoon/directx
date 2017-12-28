//
// FileName : lightclass.cpp
//
#pragma once


//
// INCLUDES
//
#include <DirectXMath.h>

using namespace DirectX;


//
// Class Name : LightClass
//
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float, float, float, float);		// 주변광 색을 설정 
	void SetDiffuseColor(float, float, float, float);		// 분산 색을 설정
	void SetDirection(float, float, float);					// 빛의 방향을 설정
	void SetSpecularColor(float, float, float, float);		// 반사광의 색을 설정
	void SetSpecularPower(float);							// 반사의 정도를 설정

	XMFLOAT4 GetAmbientColor();								// 주변광 색을 가져옴
	XMFLOAT4 GetDiffuseColor();								// 분산 색을 가져옴
	XMFLOAT3 GetDirection();								// 빛의 방향을 가져옴
	XMFLOAT4 GetSpecularColor();							// 반사광의 색을 가져옴
	float    GetSpecularPower();							// 반사의 정도를 가져옴

private:
	XMFLOAT4 m_ambientColor;								// 주변광 색
	XMFLOAT4 m_diffuseColor;								// 분산광 색
	XMFLOAT3 m_direction;									// 빛의 방향
	XMFLOAT4 m_specularColor;								// 반사광 색
	float    m_specularPower;								// 반사 정도
};