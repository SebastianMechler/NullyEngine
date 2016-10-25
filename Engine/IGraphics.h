#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
	struct SGraphicsParams
	{
		uint32_c width;
		uint32_c height;
		bool_c fullscreenEnabled;
		bool_c vsyncEnabled;
	};

	class IGraphics
	{
	public:
		virtual void Init(const SGraphicsParams& params) = 0;
		virtual void Shutdown() = 0;

	protected:

	};
}


