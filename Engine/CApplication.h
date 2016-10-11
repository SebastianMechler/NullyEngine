#pragma once
#include "stdafx.h"
#include "Datatypes.h"
#include "ECoreResult.h"
#include "CWindow.h"
#include "IGame.h"

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
		class IGame* pGame;
	};

	class CApplication
	{
	public:
		static ECoreResult Run(const SAppParams& params);
		static CApplication* GetInstance() { return m_pInstance; }

	public:
		~CApplication();

		static Graphics::CWindow* GetWindow() { return m_pInstance->m_pWindow; }
		static class IGame* GetGame() { return m_pInstance->m_pGame; }

	private:
		CApplication(class IGame* pGame);
		ECoreResult Init(const SAppParams& params);
		ECoreResult Shutdown();

	private:
		static CApplication* m_pInstance;
		Graphics::CWindow* m_pWindow;
		IGame* m_pGame;

	};
}

