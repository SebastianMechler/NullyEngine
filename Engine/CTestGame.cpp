#include "stdafx.h"
#include "CTestGame.h"

using namespace std;
using namespace Nully;

CTestGame::CTestGame()
{
}

CTestGame::~CTestGame()
{
}

void Nully::CTestGame::Init()
{
	cout << "CTestGame::Init()" << endl;

	IGame* pGame = CApplication::GetGame();
	CTestGame* pTestGame = dynamic_cast<CTestGame*>(pGame);

	CWindow* pWindow = CApplication::GetWindow();
	CGraphicsDX11* pGraphicsDX11 = (CGraphicsDX11*)CApplication::GetGraphics();

	CMaterial* pMaterial = pGraphicsDX11->LoadMaterial(L"shader/basic.hlsl");
	if (pMaterial)
		delete pMaterial;
}

void Nully::CTestGame::Shutdown()
{
	cout << "CTestGame::Shutdown()" << endl;
}

void Nully::CTestGame::Update()
{
	//cout << "CTestGame::Update()" << endl;

	
}
