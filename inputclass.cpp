//
// FileName : inputclass.cpp
//
#include "inputclass.h"

//
// CLASS FUNCTION
// 

// ������
InputClass::InputClass()
{
}

// ���� ������
InputClass::InputClass(const InputClass& other)
{
}

// �Ҹ���
InputClass::~InputClass()
{
}

// ����
void InputClass::Initialize()
{
	// ��� Ű���� ������ ���� ���·� �ʱ�ȭ
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return;
}

// Ű ����
void InputClass::KeyDown(unsigned int input)
{
	// Ű�� ���ȴٸ� �� ���¸� �迭�� ����
	m_keys[input] = true;

	return;
}

// Ű ���� ����
void InputClass::KeyUp(unsigned int input)
{
	// Ű�� �������ٸ� �� ���¸� �迭�� ����
	m_keys[input] = false;

	return;
}

// Ű�� ���ȴ��� Ȯ��
bool InputClass::IsKeyDown(unsigned int key)
{
	// ���� Ű�� ���¸� ��ȯ
	return m_keys[key];
}
