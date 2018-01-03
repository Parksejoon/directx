//
// FileName : inputclass.h
//
#pragma once


//
// PRE-PROCESSING DIRECTIVES
//
#define DIRECTINPUT_VERSION 0x0800


//
// LINKING
//
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//
// INCLUDES
//
#include <dinput.h>


//
// Class Name : InputClass
//
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);				// 초기화
	void Shutdown();										// 종료
	bool Frame();											// 프레임

	bool IsKeyDown(byte);									// 해당 키가 눌렸는지 체크하는 함수
	bool IsEscapePressed();									// 디스케이프 문자를 입력했는지 확인
	void GetMouseLocation(int&, int&);						// 마우스의 좌표를 가져오는 함수
	void GetKeyboardKey();									// 현재 눌린 키를 가져오는 함수

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
	int m_pressKey;
};
