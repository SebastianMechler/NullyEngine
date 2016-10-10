#include "CSocket.h"

namespace Nully
{
  namespace Network
  {
    CSocket::CSocket()
     : m_socket(0)
    {
    }
    CSocket::~CSocket()
    {
      WSACleanup();
    }

    ECoreResult CSocket::Open(const SocketFamily a_family, SocketType const a_type)
    {
      if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
      {
        // dll-call
        return ECoreResult::SocketOpenError;
      }

      Close();

      m_socket = socket(static_cast<int32_c>(a_family), static_cast<int32_c>(a_type), 0);

      if (m_socket == INVALID_SOCKET)
      {
        HRESULT x = WSAGetLastError();
        return ECoreResult::SocketOpenError;
      }
      
      return ECoreResult::Success;
    }
    ECoreResult CSocket::Connect(const SocketFamily a_family, const SocketPort a_port, const char_c* a_remoteAddress) const
    {
      if (m_socket == INVALID_SOCKET)
      {
        return ECoreResult::SocketInvalidError;
      }
      
      SOCKADDR_IN in = {0};
      in.sin_family = static_cast<ADDRESS_FAMILY>(a_family);
      in.sin_port = htons(static_cast<u_short>(a_port));

      ULONG addr = 0;
      if (inet_pton(static_cast<INT>(a_family), a_remoteAddress, &addr) == -1)
      {
        // inet_pton failed...
      }

      in.sin_addr.S_un.S_addr = addr;

      if (connect(m_socket, reinterpret_cast<sockaddr*>(&in), sizeof(sockaddr_in)) == SOCKET_ERROR)
      {
        return ECoreResult::SocketConnectError;
      }

      return ECoreResult::Success;
    }
    ECoreResult CSocket::Send(const char_c* a_buffer, uint32_c a_bufferSize) const
    {
      if (m_socket == INVALID_SOCKET)
      {
        return ECoreResult::SocketInvalidError;
      }

      if (a_buffer == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      if (send(m_socket, a_buffer, a_bufferSize, 0) == SOCKET_ERROR)
      {
        return ECoreResult::SocketSendError;
      }

      return ECoreResult::Success;
    }

    ECoreResult CSocket::Receive(char_c* a_buffer, uint32_c a_bufferSize) const
    {
      if (m_socket == INVALID_SOCKET)
      {
        return ECoreResult::SocketInvalidError;
      }

      if (a_buffer == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      if (recv(m_socket, a_buffer, a_bufferSize, 0) == SOCKET_ERROR)
      {
        return ECoreResult::SocketSendError;
      }

      return ECoreResult::Success;
    }
    inline void CSocket::Close()
    {
      if (m_socket != INVALID_SOCKET)
      {
        closesocket(m_socket);
      }
    }
  }
}