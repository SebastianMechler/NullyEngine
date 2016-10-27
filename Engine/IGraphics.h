#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
	struct SGraphicsParams
	{
		bool_c vsyncEnabled;
	};

	class IGraphics
	{
	public:
		virtual void Init(const SGraphicsParams& params) = 0;
		virtual void Shutdown() = 0;
		virtual void Render() = 0;

	protected:

	};
}


