#pragma once
#include "Engine.h"

namespace Nully
{
	class CTestGame : public IGame
	{
	public:
		CTestGame();
		virtual ~CTestGame();

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void Update() override;
	};
}
