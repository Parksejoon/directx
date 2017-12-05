//
// FileName : inputclass.h
//
#pragma once

//
// Class Name : InputClass
//
class InputClass
{
public:
	// 생성자 & 소멸자
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	// 멤버 함수
	void Initialize();				// 생성

	void KeyDown(unsigned int);		// 키 눌림
	void KeyUp(unsigned int);		// 키 눌림 해제

	bool IsKeyDown(unsigned int);	// 키를 누르고있는가

private:
	// 멤버 변수
	bool m_keys[256];				// 키의 상태
};
