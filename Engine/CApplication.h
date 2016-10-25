#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "CWindow.h"
#include "IGame.h"

namespace Nully
{
	class CWindow;
	struct SWindowParams;

	struct SAppParams
	{
		SWindowParams* pWindowParams;
		SGraphicsParams* pGraphicsParams;
		class IGame* pGame;
	};

	class CApplication
	{
	public:
		static ECoreResult Run(const SAppParams& params);
		static CApplication* GetInstance() { return m_pInstance; }

	public:
		~CApplication();

		static IGraphics* GetGraphics() { return m_pInstance->m_pGraphics; }
		static CWindow* GetWindow() { return m_pInstance->m_pWindow; }
		static class IGame* GetGame() { return m_pInstance->m_pGame; }

	private:
		CApplication(class IGame* pGame);
		ECoreResult Init(const SAppParams& params);
		ECoreResult Shutdown();

	private:
		static CApplication* m_pInstance;
		CWindow* m_pWindow;
		IGraphics* m_pGraphics;
		IGame* m_pGame;

	};
}

