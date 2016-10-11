#pragma once
#include "Engine.h"

namespace Nully
{
	class IGame
	{
	public:
		IGame();
		virtual ~IGame();

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;

	protected:


	};

}
