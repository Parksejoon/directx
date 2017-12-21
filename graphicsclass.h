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
#include "lightshaderclass.h"
#include "lightclass.h"


//
// GLOBALS
//
const bool  FULL_SCREEN = false;				// 전체화면 여부
const bool  VSYNC_ENABLED = true;			// 수직동기화 여부
const float SCREEN_DEPTH = 1000.0f;			// 화면의 끝부분
const float SCREEN_NEAR = 0.1f;				// 화면의 시작부분


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
	bool Frame();							// 매 프래임마다 실행

private:
	bool Render(float);						// 렌더링

private:
	D3DClass*		    m_D3D;		    	// D3DX 
	CameraClass*	    m_Camera;			// 카메라
	ModelClass*		    m_Model;			// 모델
	LightShaderClass*	m_LightShader;		// 조명 셰이더
	LightClass*			m_Light;			// 조명
};
