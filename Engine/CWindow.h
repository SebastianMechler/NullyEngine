#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
	namespace Graphics
	{
		struct SWindowParams
		{
			HINSTANCE hInstance;
			const char_c* pTitle;
			const char_c* pClassName;
			uint32_c width;
			uint32_c height;
			bool_c resizable;
		};

		class CWindow
		{
		public:
			CWindow();
			virtual ~CWindow();

			ECoreResult Init(const SWindowParams& params);
			ECoreResult Shutdown();
			void ProcessMessages();

			void Resize(uint32_c width, uint32_c height);

			bool_c GetQuit() { return m_quit; }
			HWND GetHandle() { return m_hwnd; }
			RECT GetRect() { return m_rect; }
			uint32_c GetWidth() { return m_rect.right - m_rect.left; }
			uint32_c GetHeight() { return m_rect.bottom - m_rect.top; }

		private:
			static LRESULT CALLBACK WindowProc(
				HWND   hwnd,
				UINT   uMsg,
				WPARAM wParam,
				LPARAM lParam
			);

		private:
			static bool_c m_quit;
			SWindowParams m_params;
			HINSTANCE m_hInstance;
			HWND m_hwnd;
			LPCSTR m_pClassName;
			RECT m_rect;
		};
	}
}