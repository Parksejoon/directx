//
// Filenme : graphicsclass.h
//
#pragma once


//
// MY CLASS INCLUDES
//
#include "d3dclass.h"


//
// GLOBALS
//
const bool  FULL_SCREEN = false;
const bool  VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


//
// Class Name : GraphicsClass
//
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);	// 초기화
	void Shutdown();					// 종료
	bool Frame();						// 매 프래임마다 실행

private:
	bool Render();						// 랜더링

private:
	D3DClass* m_D3D;					// DirectX 3D를 관리하는 포인터
};
