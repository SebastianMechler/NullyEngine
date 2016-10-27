#pragma once
#include "stdafx.h"
#include "CStringA.h"
#include "CStringW.h"

namespace Nully
{
  #ifdef UNICODE
      typedef CStringW CString;
  #else
      typedef CStringA CString;
  #endif
}
