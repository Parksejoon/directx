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

	void Initialize();				// �ʱ�ȭ

	void KeyDown(unsigned int);		// Ű ����
	void KeyUp(unsigned int);		// Ű ���� ����

	bool IsKeyDown(unsigned int);	// Ű�� �������ִ°�

private:
	bool m_keys[256];				// Ű�� ����
};
