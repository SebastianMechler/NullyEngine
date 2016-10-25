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
}

void Nully::CTestGame::Shutdown()
{
	cout << "CTestGame::Shutdown()" << endl;
}

void Nully::CTestGame::Update()
{
	cout << "CTestGame::Update()" << endl;
}
