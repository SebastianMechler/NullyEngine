#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "SProcessData.h"
#include "EAllocationType.h"
#include "EProtectionType.h"

namespace Nully
{
  namespace Hacking
  {
    class CProcess
    {
    public:
      ////=======================================================================
      //// Constructor / Destructor
      ////=======================================================================

      /// @brief Default constructor
      CProcess();

      /// @brief Constructor which creates a new instance and opens the passed processID
      /// @param a_processID Unique ID from a given process
      CProcess(const uint32_c a_processID);

      /// @brief Destructor which releases used resources
      ~CProcess();

      ////=======================================================================
      //// Public Member functions
      ////=======================================================================

      /// @brief Opens a process with reading and writing flags. The process-handle will be stored internally.
      /// @param a_processID Unique ID from a given process
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessOpenError on failure
      ECoreResult Open(const uint32_c a_processID);

      /// @brief Closes the process-handle
      void Close();

      /// @brief Reads bytes of type T at the location of a_address
      /// @param a_address Valid number which will be read from
      /// @return Returns 0 if any error occoured, else the read value will be returned
      template <typename T>
      T Read(const void* a_address) const;

      /// @brief Writes a value of specific type to the passed address
      /// @param a_address Valid number which will be read from
      /// @param a_value Value which will be written to the location of a_address
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessWriteError or ECoreResult::Nullptr on failure
      template <typename T>
      ECoreResult Write(void* a_address, const T a_value) const;

      /// @brief Reads a byte-string from address to the passed buffer
      /// @param a_address Valid number which will be read from
      /// @param a_buffer Buffer which will receive the read bytes
      /// @param a_bufferSize Size of the buffer, to prevent overwriting memory
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessReadError or ECoreResult::Nullptr on failure
      ECoreResult ReadText(const void* a_address, uchar_c* a_buffer, const size_c a_bufferSize) const;

      /// @brief Writes a byte-string to address
      /// @param a_address Valid number which will be read from
      /// @param a_buffer Buffer which contains the data of bytes
      /// @param a_bufferSize Size of the buffer, to prevent overwriting memory
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessWriteError or ECoreResult::Nullptr on failure
      ECoreResult WriteText(void* a_address, const uchar_c* a_buffer, const size_c a_bufferSize) const;

      /// @brief Allocates memory inside the process. Allocated memory is initialized with zero.
      /// @param a_address The pointer that specifies a desired starting address for the region of pages that you want to allocate.
      /// @param a_size The size of the region of memory to allocate, in bytes.
      /// @param a_allocation The type of memory allocation.
      /// @param a_protection The memory protection for the region of pages to be allocated.
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessAllocateError on failure
      ECoreResult VirtualAllocate(void* a_address, const size_c a_size, const EAllocationType a_allocation, const EProtectionType a_protection, void*& a_allocatedBaseAddress);

      /// @brief Changes the protectionstate of memory inside the process.
      /// @param a_address A pointer to the base address of the region of pages whose access protection attributes are to be changed.
      /// @param a_size The size of the region whose access protection attributes are changed, in bytes.
      /// @param a_newProtection The memory protection option.
      /// @param a_oldProtection A pointer to a variable that receives the previous access protection of the first page in the specified region of pages. If this parameter is NULL or does not point to a valid variable, the function fails.
      /// @return Returns ECoreResult::Success on success and ECoreResult::ProcessProtectError on failure.
      ECoreResult VirtualProtect(void* a_address, const size_c a_size, const EProtectionType a_newProtection, EProtectionType*& a_oldProtection);

      /// @brief Calculates the base module address
      /// @return Returns a valid pointer to address on success and nullptr on failure
      void* GetBaseAddress();

      /// @brief Dumps the data to a file. If the file already exists, the contents will be deleted.
      /// @param a_processData Data which is obtained from GetProcessListByName.
      /// @param a_path Path to the file.
      /// @result On Success returns ECoreResult::Success and on failure returns ECoreResult::Nullptr.
      ECoreResult CProcess::DumpToFile(const std::vector<SProcessData>* a_processData, const char_c * a_path);

      /// @brief Sets debug privileges to the executeable in order to read/write to other processes. Use this if you have trouble with reading/writing.
      /// @return Returns true on success and false on failure
      static bool_c SetDebugPrivilegeState(const bool_c a_state);

      /// @brief Retrieves a list processes. Process without name will be flagged with "unknown"
      /// @param a_processName Name of the searching process or nullptr to receive all current processes.
      /// @param a_getFullProcessPathName Optional, set this to true if you want the path to the executeable file on the harddisk.
      static std::vector<SProcessData> GetProcessListByName(const char_c* a_processName, const bool a_getFullProcessPathName = false);

    private:

      ////=======================================================================
      //// Private Member functions
      ////=======================================================================
      /// @brief Deleted copy constructor
      CProcess(const CProcess&) = delete;

      /// @brief Deleted move constructor
      CProcess(const CProcess&&) = delete;

      /// @brief Deleted assignment operator
      CProcess& operator=(const CProcess&) = delete;
        

      ////=======================================================================
      //// Private Members
      ////=======================================================================
      static const uint32_c m_maxProcesses = 8096;
      void* m_processHandle;
      uint32_c m_processID;
    };
  }
}

// template function implementation
#include "CProcess.hpp" 
