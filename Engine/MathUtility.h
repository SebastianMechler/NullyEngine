#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

#define NULLY_PI 3.1415926535897932384626433832795028f
#define NULLY_RAD_TO_DEG	180.0f / NULLY_PI
#define NULLY_DEG_TO_RAD	NULLY_PI / 180.0f

namespace Nully
{
	template<typename T>
	inline T clamp(T value, T min, T max)
	{
		return value < min ? min : (value > max ? max : value);
	}
}