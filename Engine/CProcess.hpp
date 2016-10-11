#pragma once
#include "stdafx.h"

namespace Nully
{
  namespace Hacking
  {
    template <typename T>
    T CProcess::Read(const void* a_address) const
    {
      if (this->m_processHandle == nullptr || a_address == nullptr)
      {
        return 0;
      }

      T readValue = T();
      if (ReadProcessMemory(this->m_processHandle, a_address, &readValue, sizeof(readValue), nullptr) == 0)
      {
        return 0;
      }
      return readValue;
    }

    template <typename T>
    ECoreResult CProcess::Write(void* a_address, const T a_value) const
    {
      if (this->m_processHandle == nullptr || a_address == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      if (WriteProcessMemory(this->m_processHandle, a_address, &a_value, sizeof(a_value), nullptr) == 0)
      {
        return ECoreResult::ProcessWriteError;
      }
      else
      {
        return ECoreResult::Success;
      }
    }
  }
}
