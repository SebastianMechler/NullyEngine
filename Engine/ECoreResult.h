#pragma once
#include "stdafx.h"
#include "Datatypes.h"

namespace Nully
{
  enum class ECoreResult : uint8_c
  {
    Success,
    Nullptr,

    ProcessWriteError,
    ProcessOpenError,
    ProcessReadError,
    ProcessAllocateError,
    ProcessProtectError,

    FileOpenError,
    FileReadError,
    FileWriteError,

    SocketOpenError,
    SocketSendError,
    SocketReceiveError,
    SocketInvalidError,
    SocketConnectError,
  };
}
