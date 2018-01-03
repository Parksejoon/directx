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

	bool Initialize(HINSTANCE, HWND, int, int);				// �ʱ�ȭ
	void Shutdown();										// ����
	bool Frame();											// ������

	bool IsKeyDown(byte);									// �ش� Ű�� ���ȴ��� üũ�ϴ� �Լ�
	bool IsEscapePressed();									// �������� ���ڸ� �Է��ߴ��� Ȯ��
	void GetMouseLocation(int&, int&);						// ���콺�� ��ǥ�� �������� �Լ�
	void GetKeyboardKey();									// ���� ���� Ű�� �������� �Լ�

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
