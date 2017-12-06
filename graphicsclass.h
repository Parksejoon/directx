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
	// 생성자 & 소멸자
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	// 멤버 함수
	bool Initialize(int, int, HWND);	// 생성
	void Shutdown();					// 종료
	bool Frame();						// 매 프래임마다 실행

private:
	bool Render();						//랜더링

private:
	// 멤버 변수
	D3DClass* m_D3D;
};
