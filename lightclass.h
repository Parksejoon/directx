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

	void SetAmbientColor(float, float, float, float);		// �ֺ��� ���� ���� 
	void SetDiffuseColor(float, float, float, float);		// �л� ���� ����
	void SetDirection(float, float, float);					// ���� ������ ����
	void SetSpecularColor(float, float, float, float);		// �ݻ籤�� ���� ����
	void SetSpecularPower(float);							// �ݻ��� ������ ����

	XMFLOAT4 GetAmbientColor();								// �ֺ��� ���� ������
	XMFLOAT4 GetDiffuseColor();								// �л� ���� ������
	XMFLOAT3 GetDirection();								// ���� ������ ������
	XMFLOAT4 GetSpecularColor();							// �ݻ籤�� ���� ������
	float    GetSpecularPower();							// �ݻ��� ������ ������

private:
	XMFLOAT4 m_ambientColor;								// �ֺ��� ��
	XMFLOAT4 m_diffuseColor;								// �л걤 ��
	XMFLOAT3 m_direction;									// ���� ����
	XMFLOAT4 m_specularColor;								// �ݻ籤 ��
	float    m_specularPower;								// �ݻ� ����
};