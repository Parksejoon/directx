//
// FileName : cameraclass.cpp
//
#include "cameraclass.h"


//
// CLASS FUNCTION
//
CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	
	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// 어디를 위쪽으로 할지 정합니다.
	up.m128_f32[0] = 0.0f;
	up.m128_f32[1] = 1.0f;
	up.m128_f32[2] = 0.0f;

	// 실제 월드 안에있는 카메라의 위치를 설정합니다.
	position.m128_f32[0] = m_positionX;
	position.m128_f32[1] = m_positionY;
	position.m128_f32[2] = m_positionZ;

	// 카메라가 보고있는 위치를 기본으로 설정합니다.
	lookAt.m128_f32[0] = 0.0f;
	lookAt.m128_f32[1] = 0.0f;
	lookAt.m128_f32[2] = 1.0f;

	// X, Y, Z 축을 라디안값으로 설정합니다.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// 회전 매트릭스를 생성합니다.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// 카메라가 보고있는 위치와 upvector를 회전시킵니다. 
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// 회전된 카메라의 위치를 뷰어위치로 옮깁니다.
	lookAt = position + lookAt;

	// 뷰 매트릭스를 생성합니다. 
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;

	return;
}
