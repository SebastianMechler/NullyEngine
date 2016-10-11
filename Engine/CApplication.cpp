#include "CApplication.h"

using namespace Nully;
using namespace Nully::Graphics;

CApplication* CApplication::m_pInstance;

ECoreResult CApplication::Run(const SAppParams& params, IGame* pGame)
{
	ECoreResult result = ECoreResult::Success;

	// Init Application
	m_pInstance = new CApplication();
	result = m_pInstance->Init(params);
	if (result != ECoreResult::Success)
	{
		return result;
	}

	// Get Window
	m_pInstance->m_pWindow = CWindow::GetInstance();
	CWindow* pWindow = m_pInstance->m_pWindow;

	// Init Game
	pGame->Init();

	// Start Loop
	bool quit = false;
	while (!quit)
	{
		// Process Windows Messages
		pWindow->ProcessMessages();
		quit = pWindow->GetQuit();

		// Update
		pGame->Update(); // TODO: deltaTime

		// TOOD: Render

	}

	// Shutdown Game
	pGame->Shutdown();
	// Shutdown Application
	m_pInstance->Shutdown();

	return ECoreResult::Success;
}

CApplication::CApplication()
	: m_pWindow(nullptr)
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

	CWindow::CreateInstance(*params.pWindowParams);

	return ECoreResult::Success;
}

ECoreResult CApplication::Shutdown()
{
	CWindow::DestroyInstance();

	return ECoreResult::Success;
}
