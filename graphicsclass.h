//
// Filenme : graphicsclass.h
//
#pragma once


//
// MY CLASS INCLUDES
//
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"


//
// GLOBALS
//
const bool  FULL_SCREEN = false;		// ��üȭ�� ����
const bool  VSYNC_ENABLED = true;		// ��������ȭ ����
const float SCREEN_DEPTH = 1000.0f;		// ȭ���� ���κ�
const float SCREEN_NEAR = 0.1f;			// ȭ���� ���ۺκ�


//
// Class Name : GraphicsClass
//
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);	// �ʱ�ȭ
	void Shutdown();					// ����
	bool Frame();						// �� �����Ӹ��� ����

private:
	bool Render();						// ������

private:
	D3DClass*		  m_D3D;			// D3DX ����
	CameraClass*	  m_Camera;			// ī�޶� ����
	ModelClass*		  m_Model;			// �� ����
	ColorShaderClass* m_ColorShader;	// ���̴� ����
};
