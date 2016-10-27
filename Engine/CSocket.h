#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "ISocket.h"

namespace Nully
{
  class CSocket
  {
  public:
    CSocket();
    ~CSocket();
    ECoreResult Open(const SocketFamily a_family, const SocketType a_type);
    ECoreResult Connect(const SocketFamily a_family, const SocketPort a_port, const char_c* a_remoteAddress) const;
    ECoreResult Send(const char_c* a_buffer, const uint32_c a_bufferSize) const;
    ECoreResult Receive(char_c* a_buffer, uint32_c a_bufferSize) const;
    inline void Close();

  private:
    SOCKET m_socket;
    WSADATA m_wsaData;
  };
}