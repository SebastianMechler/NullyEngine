#pragma once
#include "Engine.h"

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
			bool_c GetQuit() { return m_quit; }

		private:
			static CWindow* m_pInstance;
			bool m_quit;
			HINSTANCE m_hInstance;
			HWND m_hwnd;
			LPCSTR m_pClassName;
		};
	}
}