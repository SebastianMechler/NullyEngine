#pragma once
#include "stdafx.h"

namespace Nully
{
  // 8 Bit
  typedef unsigned __int8 uint8_c;
  typedef __int8 int8_c;
  typedef unsigned __int8 uchar_c;
  typedef __int8 char_c;
  typedef bool bool_c;

  // 16 Bit
  typedef unsigned __int16 uint16_c;
  typedef __int16 int16_c;
  typedef wchar_t wchar_c;

  // 32 Bit
  typedef unsigned __int32 uint32_c;
  typedef __int32 int32_c;
  typedef float float_c;

  // 64 Bit
  typedef unsigned __int64 uint64_c;  
  typedef __int64 int64_c;
  typedef double double_c;

  // Language Specific
#ifdef UNICODE
  typedef wchar_c tchar_c;
#else
  typedef char_c tchar_c;
#endif

// architecture-specific
#ifdef _WIN64
  typedef uint64_c size_c;
#else
  typedef uint32_c size_c;
#endif
}
