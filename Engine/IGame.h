#pragma once
#include "stdafx.h"
#include "Engine.h"

namespace Nully
{
	class IGame
	{
	public:
    virtual ~IGame() {};

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;

	protected:


	};

}
