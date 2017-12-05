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
	// ������ & �Ҹ���
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	// ��� �Լ�
	void Initialize();				// ����

	void KeyDown(unsigned int);		// Ű ����
	void KeyUp(unsigned int);		// Ű ���� ����

	bool IsKeyDown(unsigned int);	// Ű�� �������ִ°�

private:
	// ��� ����
	bool m_keys[256];				// Ű�� ����
};
