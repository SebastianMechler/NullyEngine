#include "stdafx.h"
#include "Engine.h"

#include "CTestGame.h"

using namespace Nully;
using namespace Nully::Math;
using namespace Nully::Level;
using namespace std;

void InitApp()
{
	SWindowParams wndParams = {};
	wndParams.hInstance = GetModuleHandle(NULL);
	wndParams.pTitle = "NullyEngine";
	wndParams.pClassName = "NullyWndClassName";
	wndParams.width = 800;
	wndParams.height = 600;
	wndParams.resizable = false;

	SGraphicsParams graphicsParams = {};
	graphicsParams.width = wndParams.width;
	graphicsParams.height = wndParams.height;
	graphicsParams.vsyncEnabled = false;
	graphicsParams.fullscreenEnabled = false;

	CTestGame testGame;

	SAppParams appParams = {};
	appParams.pWindowParams = &wndParams;
	appParams.pGame = &testGame;
	appParams.pGraphicsParams = &graphicsParams;

	ECoreResult result = CApplication::Run(appParams);
}

//void InitWindow()
//{
//	SWindowParams wndParams = {};
//	wndParams.hInstance = GetModuleHandle(NULL);
//	wndParams.pTitle = "NullyEngine";
//	wndParams.pClassName = "NullyWndClassName";
//	wndParams.width = 800;
//	wndParams.height = 600;
//	CWindow::CreateInstance(wndParams);
//
//	bool quit = false;
//	while (!quit)
//	{
//		CWindow::GetInstance()->ProcessMessages();
//		quit = CWindow::GetInstance()->GetQuit();
//
//		// Update
//		// Render
//	}
//
//	CWindow::DestroyInstance();
//}

void TestMaze()
{
	CMazeDepthFirst maze;
	SMazeParams params;
	params.width = 10;
	params.height = 10;
	params.seed = 1337;
	maze.Generate(params);
	maze.ShowDebugMaze("o", ".");

	cout << endl << endl;
}

void main()
{
  CMatrix4x4 matrix = CMatrix4x4::identity;

	InitApp();
	//TestMaze();
	//InitWindow();
}

