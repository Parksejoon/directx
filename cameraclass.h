//
// FileName : cameraclass.h
//
#pragma once



//
// INCLUDES
//
#include <DirectXMath.h>

using namespace DirectX;


//
// Class Name : CameraClass
//
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);			// ��ǥ ����
	void SetRotation(float, float, float);			// ȸ�� ����

	XMFLOAT3 GetPosition();							// ��ǥ�� �������� �Լ�
	XMFLOAT3 GetRotation();							// ������ �������� �Լ�

	void Render();									// �������� ����
	void GetViewMatrix(XMMATRIX&);					// �� ����� �������� �Լ�

private:
	float m_positionX, m_positionY, m_positionZ;	// ī�޶��� ��ġ(��ǥ)
	float m_rotationX, m_rotationY, m_rotationZ;	// ī�޶��� ����
	XMMATRIX m_viewMatrix;							// �� ���
};
