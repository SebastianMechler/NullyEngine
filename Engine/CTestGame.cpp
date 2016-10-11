#include "CTestGame.h"

using namespace std;
using namespace Nully;
using namespace Nully::Graphics;

Nully::CTestGame::CTestGame()
{
}

Nully::CTestGame::~CTestGame()
{
}

void Nully::CTestGame::Init()
{
	cout << "CTestGame::Init()" << endl;

	IGame* pGame = CApplication::GetInstance()->GetGame();
	CTestGame* pTestGame = dynamic_cast<CTestGame*>(pGame);

	CWindow* pWindow = CApplication::GetInstance()->GetWindow();
}

void Nully::CTestGame::Shutdown()
{
	cout << "CTestGame::Shutdown()" << endl;
}

void Nully::CTestGame::Update()
{
	cout << "CTestGame::Update()" << endl;
}
