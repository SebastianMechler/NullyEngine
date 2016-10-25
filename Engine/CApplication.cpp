#include "stdafx.h"
#include "CApplication.h"
#include "IGraphics.h"
#include "CGraphicsDX11.h"

using namespace Nully;

CApplication* CApplication::m_pInstance;

ECoreResult CApplication::Run(const SAppParams& params)
{
	ECoreResult result = ECoreResult::Success;

	// Init Application
	m_pInstance = new CApplication(params.pGame);
	result = m_pInstance->Init(params);
	if (result != ECoreResult::Success)
	{
		return result;
	}

	// Start Loop
	bool quit = false;
	while (!quit)
	{
		// Process Windows Messages
		m_pInstance->m_pWindow->ProcessMessages();
		quit = m_pInstance->m_pWindow->GetQuit();

		// Update
		m_pInstance->m_pGame->Update(); // TODO: deltaTime
		
		// TODO: Render

	}

	// Shutdown
	m_pInstance->Shutdown();

	return ECoreResult::Success;
}

CApplication::CApplication(IGame* pGame)
	: m_pWindow(nullptr),
		m_pGame(pGame)
{
}

CApplication::~CApplication()
{
}

ECoreResult CApplication::Init(const SAppParams& params)
{
	if (params.pWindowParams == nullptr)
	{
		return ECoreResult::Nullptr;
	}

	m_pWindow = new CWindow();
	m_pWindow->Init(*params.pWindowParams);

	m_pGraphics = new CGraphicsDX11();
	m_pGraphics->Init(*params.pGraphicsParams);

	m_pGame->Init();

	return ECoreResult::Success;
}

ECoreResult CApplication::Shutdown()
{
	m_pGame->Shutdown();
	m_pGraphics->Shutdown();
	m_pWindow->Shutdown();

	return ECoreResult::Success;
}
