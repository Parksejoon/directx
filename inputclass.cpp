//
// FileName : inputclass.cpp
//
#include "inputclass.h"

//
// CLASS FUNCTION
// 

// 생성자
InputClass::InputClass()
{
}

// 복사 생성자
InputClass::InputClass(const InputClass& other)
{
}

// 소멸자
InputClass::~InputClass()
{
}

// 생성
void InputClass::Initialize()
{
	// 모든 키들을 눌리지 않은 상태로 초기화
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return;
}

// 키 눌림
void InputClass::KeyDown(unsigned int input)
{
	// 키가 눌렸다면 그 상태를 배열에 저장
	m_keys[input] = true;

	return;
}

// 키 눌림 해제
void InputClass::KeyUp(unsigned int input)
{
	// 키가 떼어졌다면 그 상태를 배열에 저장
	m_keys[input] = false;

	return;
}

// 키가 눌렸는지 확인
bool InputClass::IsKeyDown(unsigned int key)
{
	// 현재 키의 상태를 반환
	return m_keys[key];
}
