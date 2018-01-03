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


	// 마우스 커서의 위치를 사용하기 위해 화면의 크기를 저장합니다.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// 화면 위의 마우스의 위치를 초기화합니다.
	m_mouseX = 0;
	m_mouseY = 0;

	// direct input 인터페이스를 초기화합니다.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 키보드의 direct input 인터페이스를 초기화합니다.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 데이터 형식을 설정합니다.
	// 이 경우에는 키보드 이므로 미리 정의된 데이터 형식을 사용할 수 있습니다.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// 키보드 협력 레벨을 배제 상태로 설정합니다.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// 키보드의 접근권을 취득합니다.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// 마우스의 direct input 인터페이스를 초기화합니다.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 데이터 형식을 지정합니다.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// 마우스 협력 레벨을 비배제 상태로 설정합니다.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// 마우스의 접근권을 취득합니다.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void InputClass::Shutdown()
{
	// 마우스를 할당 해제합니다.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// 키보드를 할당 해제합니다.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// direct input의 메인 인터페이스를 초기화합니다.
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


	// 지금의 키보드 상태를 읽어들입니다.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	// 지금의 마우스 상태를 읽어들입니다.
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	// 마우스와 키보드의 변화를 진행합니다.
	ProcessInput();

	return true;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// 키보드 장치를 읽어옵니다.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// 만약 키보드의 포커스를 잃었거나 취득권이 없으면 컨트롤을 다시 가져옵니다.
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


	// 마우스 장치를 읽어옵니다.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// 마우스의 포커스를 잃었거나 취득권이 없으면 컨트롤을 다시 가져옵니다.
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
	// 마우스 커서의 위치를 프래임마다 갱신해줍니다.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// 마우스의 위치가화면 밖으로 나가지 않도록 보호합니다.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	//// 누르고있는 키를 가져옵니다.
	//m_pressKey = m_keyboardState[]

	return;
}

bool InputClass::IsKeyDown(byte key)
{
	// 키가 눌렸는지 검사합니다.
	if (m_keyboardState[key] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsEscapePressed()
{
	// 창을 종료하는 키를 눌렀는지를 검사합니다.
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
