//
// Filenme : graphicsclass.h
//
#pragma once


//
// GLOBALS
//
const bool  FULL_SCREEN = false;				// 전체화면 여부
const bool  VSYNC_ENABLED = true;				// 수직동기화 여부
const float SCREEN_DEPTH = 1000.0f;				// 화면의 끝부분
const float SCREEN_NEAR = 0.1f;					// 화면의 시작부분


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

	bool Initialize(int, int, HWND);		// 초기화
	void Shutdown();						// 종료
	bool Frame(int, int);					// 매 프래임마다 실행
	bool Render();							// 렌더링

private:
	D3DClass*		    m_D3D;		    	// D3DX 
	CameraClass*	    m_Camera;			// 카메라
	TextClass*			m_Text;				// 텍스트
	//TextureShaderClass*	m_TextureShader;	// 텍스쳐 셰이더
	//BitmapClass*			m_Bitmap;			// 비트맵
	//ModelClass*		    m_Model;			// 모델
	//LightShaderClass*		m_LightShader;		// 조명 셰이더
	//LightClass*			m_Light;			// 조명
};
