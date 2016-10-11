#include "CWindow.h"

using namespace Nully;
using namespace Nully::Graphics;

bool_c CWindow::m_quit;

LRESULT CWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_QUIT:
	case WM_DESTROY:
		CWindow::m_quit = true;
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

CWindow::CWindow()
{
	
}

CWindow::~CWindow()
{
	
}

ECoreResult CWindow::Init(const SWindowParams& params)
{
	ECoreResult result = ECoreResult::Success;

	m_quit = false;
	m_pClassName = params.pClassName;

	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = 0;
	wndClass.lpfnWndProc = CWindow::WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = params.hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = m_pClassName;
	wndClass.hIconSm = NULL;

	RegisterClassEx(&wndClass);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		wndClass.lpszClassName,
		params.pTitle,
		WS_OVERLAPPEDWINDOW,
		screenWidth / 4,
		screenHeight / 4,
		params.width,
		params.height,
		NULL,
		NULL,
		params.hInstance,
		NULL);

	ShowWindow(m_hwnd, SW_SHOW);

	return result;
}

ECoreResult CWindow::Shutdown()
{
	ECoreResult result = ECoreResult::Success;

	DestroyWindow(m_hwnd);
	UnregisterClass(m_pClassName, m_hInstance);

	return result;
}

void CWindow::ProcessMessages()
{
	MSG msg;
	BOOL ret;

	do
	{
		ret = PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE);

		if (ret != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} while (ret != 0);
}
