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

	void SetPosition(float, float, float);			// 좌표 설정
	void SetRotation(float, float, float);			// 회전 설정

	XMFLOAT3 GetPosition();							// 좌표를 가져오는 함수
	XMFLOAT3 GetRotation();							// 각도를 가져오는 함수

	void Render();									// 렌더링을 실행
	void GetViewMatrix(XMMATRIX&);					// 뷰 행렬을 가져오는 함수

private:
	float m_positionX, m_positionY, m_positionZ;	// 카메라의 위치(좌표)
	float m_rotationX, m_rotationY, m_rotationZ;	// 카메라의 각도
	XMMATRIX m_viewMatrix;							// 뷰 행렬
};
