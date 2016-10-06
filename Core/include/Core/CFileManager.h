#pragma once
#include <iostream>
#include <Windows.h>

#include "Datatypes.h"
#include "EFileMode.h"
#include "ECoreResult.h"
#include "CString.h"
#include "EFilePosition.h"

namespace Nully
{
  namespace Tools
  {
    class CFileManager
    {
    public:
      ////=======================================================================
      //// Constructor / Destructor
      ////=======================================================================

      /// @brief Default-Constructor.
      CFileManager();

      /// @brief Constructor which opens the diresed file.
      /// @param a_path: Path with filename.
      /// @param a_mode: File-Mode e. g. for Read, Write, ...
      CFileManager(const char_c* a_path, const EFileMode a_mode);

      /// @brief Destructor which closes open resources.
      ~CFileManager();

      ////=======================================================================
      //// Public Member functions
      ////=======================================================================

      /// @brief Opens the desired file.
      /// @param a_path Path with filename.
      /// @param a_mode File-Mode e. g. for Read, Write, ...
      /// @return Returns ECoreResult::Success on success and ECoreResult::Nullptr or ECoreResult::FileOpenError on failure.
      ECoreResult Open(const char_c* a_path, const EFileMode a_mode);

      /// @brief Reads a file (file must be opened in the correct mode).
      /// @param a_buffer: Pointer to a buffer which will receive the read-bytes.
      /// @param a_bufferSize: Size of a_buffer in bytes.
      /// @return Returns ECoreResult::Success on success and ECoreResult::Nullptr or ECoreResult::FileReadError on failure.
      ECoreResult Read(void* a_buffer, const size_c a_bufferSize) const;

      /// @brief Writes to a file (file must be opened in the correct mode).
      /// @param a_buffer: Pointer to a buffer which contains data to be written.
      /// @param a_bufferSize: Size of a_buffer in bytes.
      /// @return Returns ECoreResult::Success on success and ECoreResult::Nullptr or ECoreResult::FileWriteError on failure.
      ECoreResult Write(const void* a_buffer, const size_c a_bufferSize) const;

      /// @brief Sets the file pointer at specific position / offset.
      /// @param a_position: Position of file-pointer.
      /// @param a_offset: Offset which will be added after the position has been set.
      void SetFilePosition(const EFilePosition a_position, const int64_c a_offset = 0) const;

      /// @brief Opens a file to obtain the file-size
      /// @param path: path to the file as tchar_c string
      static uint64_c GetFileSize(const tchar_c* a_path);

    private:

      ////=======================================================================
      //// Private Member functions
      ////=======================================================================

      /// @brief Closes open resources.
      inline void Close();


      ////=======================================================================
      //// Private Members
      ////=======================================================================
      FILE* m_file = nullptr;
    };
  }
}