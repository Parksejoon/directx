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
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();				// 초기화

	void KeyDown(unsigned int);		// 키 눌림
	void KeyUp(unsigned int);		// 키 눌림 해제

	bool IsKeyDown(unsigned int);	// 키를 누르고있는가

private:
	bool m_keys[256];				// 키의 상태
};
