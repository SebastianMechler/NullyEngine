#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "NetworkTypes.h"

namespace Nully
{
  namespace Network
  {
    class INetwork
    {
    public:
      virtual ECoreResult Open(const SocketFamily a_family, const SocketType a_type) = 0;
      virtual ECoreResult Connect(const SocketFamily a_family, const SocketPort a_port, const char_c* a_remoteAddress) const = 0;
      virtual ECoreResult Send(const char_c* a_buffer, const uint32_c a_bufferSize) const = 0;
      virtual ECoreResult Receive(char_c* a_buffer, uint32_c a_bufferSize) const = 0;
      virtual inline void Close() = 0;
    };
  }
}