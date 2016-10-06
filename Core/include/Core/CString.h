#pragma once

#include "CStringA.h"
#include "CStringW.h"

namespace Nully
{
  namespace Tools
  {
    #ifdef UNICODE
        typedef CStringW CString;
    #else
        typedef CStringA CString;
    #endif
  }
}
