#pragma once

namespace Nully
{
  namespace Tools
  {
    enum class EFilePosition
    {
      Begin,
      Current,
      End, // WARNING: !NOT SUPPORTED ON ALL PLATFORMS!
    };
  }
}