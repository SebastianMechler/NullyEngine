#pragma once
#include "Engine.h"

namespace Nully
{
	namespace Graphics
	{
		class CWindow;
		struct SWindowParams;
	}

	struct SAppParams
	{
		Graphics::SWindowParams* pWindowParams;
	};

	class CApplication
	{
	public:
		static ECoreResult Run(const SAppParams& params, class IGame* pGame);
		static CApplication* GetInstance() { return m_pInstance; }

	public:
		~CApplication();

		Graphics::CWindow* GetWindow() { return m_pWindow; }

	private:
		CApplication();
		ECoreResult Init(const SAppParams& params);
		ECoreResult Shutdown();

	private:
		static CApplication* m_pInstance;
		Graphics::CWindow* m_pWindow;

	};
}

