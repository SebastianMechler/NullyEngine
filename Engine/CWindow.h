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
		};

		class CWindow
		{
		public:
			static LRESULT CALLBACK WindowProc(
				HWND   hwnd,
				UINT   uMsg,
				WPARAM wParam,
				LPARAM lParam
				);

		public:
			CWindow();
			virtual ~CWindow();

			ECoreResult Init(const SWindowParams& params);
			ECoreResult Shutdown();
			void ProcessMessages();
			bool_c GetQuit() { return m_quit; }

		private:
			static bool_c m_quit;
			HINSTANCE m_hInstance;
			HWND m_hwnd;
			LPCSTR m_pClassName;
		};
	}
}