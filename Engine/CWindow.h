#pragma once
#include "stdafx.h"

namespace Nully
{
	namespace Graphics
	{
		struct SWindowParams
		{
			HINSTANCE hInstance;
			const char* pTitle;
			const char* pClassName;
			int width;
			int height;
		};

		class CWindow
		{
		public:
			static void CreateInstance(const SWindowParams& params);
			static void DestroyInstance();
			static CWindow* GetInstance();

			static LRESULT CALLBACK WindowProc(
				HWND   hwnd,
				UINT   uMsg,
				WPARAM wParam,
				LPARAM lParam
				);

		public:
			CWindow(const SWindowParams& params);
			virtual ~CWindow();
			void ProcessMessages();
			bool GetQuit() { return m_quit; }

		private:
			static CWindow* m_pInstance;
			bool m_quit;
			HINSTANCE m_hInstance;
			HWND m_hwnd;
			LPCSTR m_pClassName;
		};
	}
}