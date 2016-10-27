#include "stdafx.h"
#include "Engine.h"

#include "CTestGame.h"

using namespace Nully;
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
	graphicsParams.vsyncEnabled = false;

	CTestGame testGame;

	SAppParams appParams = {};
	appParams.pWindowParams = &wndParams;
	appParams.pGame = &testGame;
	appParams.pGraphicsParams = &graphicsParams;

	ECoreResult result = CApplication::Run(appParams);
}

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
	InitApp();
	//TestMaze();
}

