#include "stdafx.h"
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
	case WM_SIZE:
		
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
	m_params = params;
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

	RECT r;
	r.right = params.width;
	r.bottom = params.height;
	r.top = 0;
	r.left = 0;
	AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	DWORD wndStyle;
	if (params.resizable)
	{
		wndStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		wndStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
	}

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		wndClass.lpszClassName,
		params.pTitle,
		wndStyle,
		screenWidth / 4,
		screenHeight / 4,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		params.hInstance,
		NULL);

	GetClientRect(m_hwnd, &m_rect);
	
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

	while (ret = PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CWindow::Resize(uint32_c width, uint32_c height)
{
	// Adjust Window Params
	m_params.width = width;
	m_params.height = height;

	// Reinitialize Window
	Shutdown();
	Init(m_params);
}
