#include "CProcess.h"
#include "CFileManager.h"

namespace Nully
{
  namespace Hacking
  {
    CProcess::CProcess()
      : m_processHandle(nullptr), m_processID(0)
    {
    }

    CProcess::CProcess(const uint32_c a_processID)
      : m_processHandle(nullptr), m_processID(0)
    {
      Open(a_processID);
    }
    CProcess::~CProcess()
    {
      m_processHandle = nullptr;
      m_processID = 0;
      Close();
    }
    ECoreResult CProcess::Open(const uint32_c a_processID)
    {
      HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, a_processID);
      if (process == nullptr)
      {
        return ECoreResult::ProcessOpenError;
      }

      if (this->m_processHandle != nullptr)
      {
        Close();
      }
      else
      {
        this->m_processHandle = process;
        this->m_processID = a_processID;
      }

      return ECoreResult::Success;
    }
    void CProcess::Close()
    {
      if (this->m_processHandle != nullptr)
      {
        CloseHandle(this->m_processHandle);
        this->m_processHandle = nullptr;
      }
    }
    ECoreResult CProcess::ReadText(const void * a_address, uchar_c * a_buffer, const size_c a_bufferSize) const
    {
      if (this->m_processHandle == nullptr || a_buffer == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      void* nonconstAddress = const_cast<void*>(a_address); // fuck you c++, can't increment a const void* pointer... fuck off
      uint8_c* incrementableAddress = reinterpret_cast<uint8_c*>(nonconstAddress); // fuck you c++, can't increment a const void* pointer... fuck off

      uint32_c index = 0;
      for (uint32_c i = 0; i < a_bufferSize; i++)
      {
        if (ReadProcessMemory(this->m_processHandle, incrementableAddress + i, a_buffer + i, 1, nullptr) == 0)
        {
          return ECoreResult::ProcessReadError;
        }

        if (a_buffer[i] == '\0')
        {
          break;
        }

        index = i;
      }

      a_buffer[index] = '\0';

      return ECoreResult::Success;
    }
    ECoreResult CProcess::WriteText(void * a_address, const uchar_c * a_buffer, const size_c a_bufferSize) const
    {
      if (this->m_processHandle == nullptr || a_buffer == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      for (uint32_c i = 0; i < a_bufferSize; i++)
      {
        if (WriteProcessMemory(this->m_processHandle, a_address, a_buffer, a_bufferSize, nullptr) == 0)
        {
          return ECoreResult::ProcessWriteError;
        }
      }

      return ECoreResult::Success;
    }
    ECoreResult CProcess::VirtualAllocate(void * a_address, const size_c a_size, const EAllocationType a_allocation, const EProtectionType a_protection, void*& a_allocatedBaseAddress)
    {
      if (this->m_processHandle == nullptr || a_address == nullptr)
      {
        return ECoreResult::Nullptr;
      }
      
      void* resultAddress = VirtualAllocEx(m_processHandle, a_address, a_size, static_cast<DWORD>(a_allocation), static_cast<DWORD>(a_protection));
      if (resultAddress == nullptr)
      {
        return ECoreResult::ProcessAllocateError;
      }
      else
      {
        a_allocatedBaseAddress = resultAddress;
        return ECoreResult::Success;
      }
    }
    ECoreResult CProcess::VirtualProtect(void * a_address, const size_c a_size, const EProtectionType a_newProtection, EProtectionType *& a_oldProtection)
    {
      if (this->m_processHandle == nullptr || a_address == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      if (VirtualProtectEx(this->m_processHandle, a_address, a_size, static_cast<DWORD>(a_newProtection), reinterpret_cast<DWORD*>(a_oldProtection)) != 0)
      {
        return ECoreResult::ProcessProtectError;
      }

      return ECoreResult::Success;
    }
    void * CProcess::GetBaseAddress()
    {
      TCHAR processModuleName[MAX_PATH] = TEXT("<none>");

      // Get a handle to the process
      HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->m_processID);
      if (process == nullptr)
      {
        return nullptr;
      }

      // Get the base address of the module
      HINSTANCE module = nullptr;
      DWORD bytesNeeded = 0;

      if (EnumProcessModules(process, &module, sizeof(module), &bytesNeeded))
      {
        GetModuleBaseName(process, module, processModuleName, sizeof(processModuleName) / sizeof(TCHAR));
      }

      CloseHandle(process);
      return (module);
    }

    ECoreResult CProcess::DumpToFile(const std::vector<SProcessData>* a_processData, const char_c * a_path)
    {
      if (a_processData == nullptr || a_path == nullptr)
      {
        return ECoreResult::Nullptr;
      }

      Nully::Tools::CFileManager fileManager;
      
      fileManager.Open(a_path, Nully::Tools::EFileMode::Write);
      
      /*
      // sort vector
      std::sort(a_processData->begin(), a_processData->end(), 
        [](SProcessData& a, SProcessData& b) 
        {
          return a.id < b.id;
        });
        */

      for (auto it = a_processData->begin(); it != a_processData->end(); it++)
      {
        auto length = it->name.GetLength();
        if (length == 0)
        {
          continue;
        }
        char buffer[2000];

        sprintf_s(buffer, "PID: [%5i] => %s", it->id, it->name.GetCString());
        //sprintf(buffer, "PID: [%5i] => %s", it->id, it->name.GetCString());

        //fileManager.Write(it->name.GetCString(), it->name.GetLength());
        fileManager.Write(buffer, strlen(buffer));
        fileManager.Write("\r\n", 2);
      }

      return ECoreResult::Success;
    }
    bool_c CProcess::SetDebugPrivilegeState(const bool_c a_state)
    {
      HANDLE token = NULL; // handle to token
      LUID luid; // local unique identifier

      // retrieves the token from the current process which can be adjusted
      if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
      {
        return false;
      }

      // retrieves the locally unique identifier which is represented by the privilege name
      if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
      {
        return false;
      }

      // token adjustment
      TOKEN_PRIVILEGES tokenPriv;
      tokenPriv.PrivilegeCount = 1;
      tokenPriv.Privileges[0].Luid = luid;
      tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // store new token in process
      if (!AdjustTokenPrivileges(token, FALSE, &tokenPriv, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
      {
        return false;
      }

      // sucess
      return true;
    }

    std::vector<SProcessData> CProcess::GetProcessListByName(const char_c * a_processName, const bool a_getFullProcessPathName)
    {
      // get all process ids and store them in processes
      DWORD processes[CProcess::m_maxProcesses], sizeNeeded;
      EnumProcesses(&processes[0], sizeof(processes), &sizeNeeded);

      // calculate number of processes
      uint32_c numberOfProcesses = sizeNeeded / sizeof(DWORD);
      std::vector<SProcessData> processList;

      for (uint32_c i = 0; i < numberOfProcesses; i++)
      {
        HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processes[i]);

        char_c processName[MAX_PATH] = {0};
        char_c extractedProcessName[MAX_PATH] = {0};

        GetProcessImageFileName(process, &processName[0], MAX_PATH);
        
        int32_c index = Nully::Tools::CStringA::FindLast(processName, '\\');
        Nully::Tools::CStringA::ExtractCString(processName, extractedProcessName, sizeof(extractedProcessName), index + 1);

        // Release the handle to the process.
        CloseHandle(process);

        if (a_processName == nullptr || strcmp(extractedProcessName, a_processName) == 0)
        {
          // nullptr passed as processName so take all processes
          SProcessData data;
          data.id = processes[i];
          if (a_getFullProcessPathName)
          {
            data.name = processName;
          }
          else
          {
            data.name = extractedProcessName;
          }
          
          processList.push_back(data);
        }
      }
      return processList;
    }
  }
}



/*
// get all names
wchar_c processName[MAX_PATH] = L"unknown";
char processName1[MAX_PATH] = "";
// Get a handle to the process.
HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);

// Get the process name.
if (process != NULL)
{
HMODULE module;
DWORD bytesNeeded;

if (EnumProcessModules(process, &module, sizeof(module), &bytesNeeded))
{
GetModuleBaseNameA(process, module, processName1, sizeof(processName1) / sizeof(char));
}
}
if (a_processName == nullptr || wcscmp(processName, a_processName) == 0)
{
// nullptr passed as processName so take all processes
SProcessData data;
data.id = processes[i];
data.name = processName1;
processList.push_back(data);
}

// Release the handle to the process.
CloseHandle(process);
*/