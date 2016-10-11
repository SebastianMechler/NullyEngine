#pragma once
#include "stdafx.h"
#include "Datatypes.h"

namespace Nully
{
  namespace Network
  {
    enum class SocketFamily : uint8_c
    {
      ipv4 = AF_INET, // internet protocol version 4
      ipv6 = AF_INET6, // internet protocol version 6
    };

    enum class SocketType : uint8_c
    {
      Stream = SOCK_STREAM, // A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism. This socket type uses the Transmission Control Protocol (TCP) for the Internet address family (AF_INET or AF_INET6).
      Dgram = SOCK_DGRAM, // A socket type that supports datagrams, which are connectionless, unreliable buffers of a fixed (typically small) maximum length. This socket type uses the User Datagram Protocol (UDP) for the Internet address family (AF_INET or AF_INET6).
      Raw = SOCK_RAW, // A socket type that provides a raw socket that allows an application to manipulate the next upper-layer protocol header. To manipulate the IPv4 header, the IP_HDRINCL socket option must be set on the socket. To manipulate the IPv6 header, the IPV6_HDRINCL socket option must be set on the socket.
      Rdm = SOCK_RDM, // A socket type that provides a reliable message datagram. An example of this type is the Pragmatic General Multicast (PGM) multicast protocol implementation in Windows, often referred to as reliable multicast programming.
      Seqpacket = SOCK_SEQPACKET, // A socket type that provides a pseudo-stream packet based on datagrams.
    };

    enum class SocketPort : uint32_c
    {
      FTP = 21,
      HTTP = 80,
      HTTPS = 443,
    };
  }
}
