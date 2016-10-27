#pragma once
#include "stdafx.h"

namespace Nully
{
  enum class EFilePosition
  {
    Begin,
    Current,
    End, // WARNING: !NOT SUPPORTED ON ALL PLATFORMS!
  };
}