#include "stdafx.h"
#include "CFileManager.h"

namespace Nully
{
  CFileManager::CFileManager()
  {

  }

  CFileManager::CFileManager(const char_c * a_path, const EFileMode a_mode)
  {
    Open(a_path, a_mode);
  }

  ECoreResult CFileManager::Open(const char_c * a_path, const EFileMode a_mode)
  {
    CStringA openMode = "";
      
    switch (a_mode)
    {
    case EFileMode::Read:
      openMode = "rb";
      break;
    case EFileMode::Write:
      openMode = "wb";
      break;
    case EFileMode::Append:
      openMode = "ab";
      break;
    case EFileMode::ReadPlus:
      openMode = "rb+";
      break;
    case EFileMode::WritePlus:
      openMode = "wb+";
      break;
    case EFileMode::AppendPlus:
      openMode = "ab+";
      break;
    default:
      openMode = "rb";
      break;
    }

    FILE* file = nullptr;
    fopen_s(&file, a_path, openMode.GetCString());
    if (file == nullptr)
    {
      return ECoreResult::FileOpenError;
    }
    else
    {
      Close();
      this->m_file = file;
      return ECoreResult::Success;
    }
  }

  ECoreResult CFileManager::Read(void * a_buffer, const size_c a_bufferSize) const
  {
    if (this->m_file == nullptr || a_buffer == nullptr)
    {
      return ECoreResult::Nullptr;
    }

    size_c readBytes = fread(a_buffer, a_bufferSize, 1, this->m_file);
    if (readBytes != a_bufferSize)
    {
      // file-end maybe reached...
      return ECoreResult::FileReadError;
    }
    else
    {
      return ECoreResult::Success;
    }
  }

  ECoreResult CFileManager::Write(const void * a_buffer, const size_c a_bufferSize) const
  {
    if (this->m_file == nullptr || a_buffer == nullptr)
    {
      return ECoreResult::Nullptr;
    }

    size_c bytesWritten = fwrite(a_buffer, a_bufferSize, 1, this->m_file);
      
    if (bytesWritten != a_bufferSize)
    {
      return ECoreResult::FileWriteError;
    }

    return ECoreResult::Success;
  }

  void CFileManager::SetFilePosition(const EFilePosition a_position, const int64_c a_offset) const
  {
    if (this->m_file == nullptr)
    {
      return;
    }

    uchar_c pos = 0;

    switch (a_position)
    {
    case EFilePosition::Begin:
      pos = SEEK_SET;
      break;
    case EFilePosition::Current:
      pos =  SEEK_CUR;
      break;
    case EFilePosition::End:
      pos = SEEK_END;
      break;
    default:
      pos = SEEK_SET;
      break;
    }     

    _fseeki64(this->m_file, a_offset, pos);
  }

  CFileManager::~CFileManager()
  {
    Close();
  }

  uint64_c CFileManager::GetFileSize(const tchar_c * a_path)
  {
    if (a_path == nullptr)
    {
      return 0;
    }
      
    HANDLE hFile = CreateFile(a_path, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == nullptr)
    {
      return 0;
    }

    LARGE_INTEGER size;
    size.QuadPart = 0;

    ::GetFileSizeEx(hFile, &size);

    CloseHandle(hFile);

    if (size.QuadPart > 0)
    {
      return size.QuadPart;
    }

    return 0;
  }

  inline void CFileManager::Close()
  {
    if (this->m_file != nullptr)
    {
      fclose(m_file);
    }
  }
}