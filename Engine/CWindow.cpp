#include "CWindow.h"

using namespace Nully::Graphics;

CWindow* CWindow::m_pInstance;

void CWindow::CreateInstance(const SWindowParams& params)
{
	m_pInstance = new CWindow(params);
}

void CWindow::DestroyInstance()
{
	delete m_pInstance;
}

CWindow* CWindow::GetInstance()
{
	return m_pInstance;
}

LRESULT CWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_QUIT:
	case WM_DESTROY:
		CWindow::GetInstance()->m_quit = true;
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

CWindow::CWindow(const SWindowParams& params)
{
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
}

CWindow::~CWindow()
{
	DestroyWindow(m_hwnd);
	UnregisterClass(m_pClassName, m_hInstance);
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
