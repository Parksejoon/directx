//
// Filenme : graphicsclass.h
//
#pragma once


//
// GLOBALS
//
const bool  FULL_SCREEN = false;				// ��üȭ�� ����
const bool  VSYNC_ENABLED = true;				// ��������ȭ ����
const float SCREEN_DEPTH = 1000.0f;				// ȭ���� ���κ�
const float SCREEN_NEAR = 0.1f;					// ȭ���� ���ۺκ�


//
// MY CLASS INCLUDES
//
#include "d3dclass.h"
#include "cameraclass.h"
#include "textclass.h"
//#include "modelclass.h"
//#include "textureshaderclass.h"
//#include "bitmapclass.h"
//#include "lightshaderclass.h"
//#include "lightclass.h"


//
// Class Name : GraphicsClass
//
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);		// �ʱ�ȭ
	void Shutdown();						// ����
	bool Frame(int, int);					// �� �����Ӹ��� ����
	bool Render();							// ������

private:
	D3DClass*		    m_D3D;		    	// D3DX 
	CameraClass*	    m_Camera;			// ī�޶�
	TextClass*			m_Text;				// �ؽ�Ʈ
	//TextureShaderClass*	m_TextureShader;	// �ؽ��� ���̴�
	//BitmapClass*			m_Bitmap;			// ��Ʈ��
	//ModelClass*		    m_Model;			// ��
	//LightShaderClass*		m_LightShader;		// ���� ���̴�
	//LightClass*			m_Light;			// ����
};
