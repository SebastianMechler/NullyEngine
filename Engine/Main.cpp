#include "Engine.h"

using namespace Nully::Math;
using namespace Nully::Graphics;


void InitWindow()
{
	SWindowParams wndParams = {};
	wndParams.hInstance = GetModuleHandle(NULL);
	wndParams.pTitle = "NullyEngine";
	wndParams.pClassName = "NullyWndClassName";
	wndParams.width = 800;
	wndParams.height = 600;
	CWindow::CreateInstance(wndParams);

	bool quit = false;
	while (!quit)
	{
		CWindow::GetInstance()->ProcessMessages();
		quit = CWindow::GetInstance()->GetQuit();

		// Update
		// Render
	}

	CWindow::DestroyInstance();
}

void main()
{
  CMatrix4x4 matrix = CMatrix4x4::identity;

	InitWindow();

}

