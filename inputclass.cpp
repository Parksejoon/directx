//
// FileName : inputclass.cpp
//
#include "inputclass.h"


//
// CLASS FUNCTION
// 
InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// ���콺 Ŀ���� ��ġ�� ����ϱ� ���� ȭ���� ũ�⸦ �����մϴ�.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// ȭ�� ���� ���콺�� ��ġ�� �ʱ�ȭ�մϴ�.
	m_mouseX = 0;
	m_mouseY = 0;

	// direct input �������̽��� �ʱ�ȭ�մϴ�.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Ű������ direct input �������̽��� �ʱ�ȭ�մϴ�.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// ������ ������ �����մϴ�.
	// �� ��쿡�� Ű���� �̹Ƿ� �̸� ���ǵ� ������ ������ ����� �� �ֽ��ϴ�.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Ű���� ���� ������ ���� ���·� �����մϴ�.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Ű������ ���ٱ��� ����մϴ�.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// ���콺�� direct input �������̽��� �ʱ�ȭ�մϴ�.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// ������ ������ �����մϴ�.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// ���콺 ���� ������ ����� ���·� �����մϴ�.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// ���콺�� ���ٱ��� ����մϴ�.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void InputClass::Shutdown()
{
	// ���콺�� �Ҵ� �����մϴ�.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Ű���带 �Ҵ� �����մϴ�.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// direct input�� ���� �������̽��� �ʱ�ȭ�մϴ�.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

bool InputClass::Frame()
{
	bool result;


	// ������ Ű���� ���¸� �о���Դϴ�.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	// ������ ���콺 ���¸� �о���Դϴ�.
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	// ���콺�� Ű������ ��ȭ�� �����մϴ�.
	ProcessInput();

	return true;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// Ű���� ��ġ�� �о�ɴϴ�.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// ���� Ű������ ��Ŀ���� �Ҿ��ų� ������ ������ ��Ʈ���� �ٽ� �����ɴϴ�.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse()
{
	HRESULT result;


	// ���콺 ��ġ�� �о�ɴϴ�.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// ���콺�� ��Ŀ���� �Ҿ��ų� ������ ������ ��Ʈ���� �ٽ� �����ɴϴ�.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput()
{
	// ���콺 Ŀ���� ��ġ�� �����Ӹ��� �������ݴϴ�.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// ���콺�� ��ġ��ȭ�� ������ ������ �ʵ��� ��ȣ�մϴ�.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	//// �������ִ� Ű�� �����ɴϴ�.
	//m_pressKey = m_keyboardState[]

	return;
}

bool InputClass::IsKeyDown(byte key)
{
	// Ű�� ���ȴ��� �˻��մϴ�.
	if (m_keyboardState[key] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsEscapePressed()
{
	// â�� �����ϴ� Ű�� ���������� �˻��մϴ�.
	if (IsKeyDown(DIK_ESCAPE))
	{
		return true;
	}

	return false;
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;

	return;
}
