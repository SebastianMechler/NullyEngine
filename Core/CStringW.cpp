#include "Core\CStringW.h"

namespace Nully
{
  namespace Tools
  {
    // Constructor 
    CStringW::CStringW()
      : m_data(nullptr)
    {
    }

    CStringW::CStringW(const wchar_c* a_string)
      : m_data(nullptr)
    {
      AssignWString(a_string);
    }

    // Move Constructor (lvalue) 
    CStringW::CStringW(const CStringW& a_string)
      : m_data(nullptr)
    {
      AssignWString(a_string.GetCString());
    }

    void CStringW::operator=(const wchar_c * a_string)
    {
      AssignWString(a_string);
    }

    void CStringW::operator=(const CStringW& a_string)
    {
      AssignWString(a_string.GetCString());
    }

    CStringW CStringW::operator+(const CStringW & a_string) const
    {
      return operator+(a_string.GetCString());
    }

    CStringW CStringW::operator+(const wchar_c * a_string) const
    {
      size_c str1_length = 0;
      size_c str2_length = 0;
      size_c str_totalLength = 0;
      auto pStr2 = a_string;
      CStringW concatString;
      
      // get str-length of string1
      if (this->m_data != nullptr)
      {
        str1_length = wcslen(m_data);
      }

      // get str-length of string2
      if (pStr2 != nullptr)
      {
        str2_length = wcslen(pStr2);
      }

      str_totalLength = str1_length + str2_length + 1; // + 1 for nulltermination
      if (str_totalLength == 1)
      {
        return concatString;
      }
      else if (str1_length == 0)
      {
        return a_string;
      }
      else if (str2_length == 0)
      {
        return *this;
      }

      // reserve bytes
      wchar_c* pBuffer = concatString.ReserveWideBytes(str_totalLength);

      // memcpy bytes from string1 into buffer and then memcpy string2 into buffer
      size_c offset = 0;
      if (str1_length > 0)
      {
        memcpy(pBuffer, this->GetCString(), str1_length);
        offset += str1_length;
      }

      if (str2_length > 0)
      {
        memcpy(pBuffer + offset, pStr2, str2_length);
        offset += str2_length;
      }

      // add null-termination
      *(pBuffer + str_totalLength) = '\0';

      // set new buffer pointer
      concatString.m_data = pBuffer;

      return concatString;
    }

    void CStringW::operator+=(const CStringW & a_string)
    {
      size_c str1_length = 0;
      size_c str2_length = 0;
      size_c str_totalLength = 0;
      auto pStr2 = a_string.GetCString();

      // get str-length of string1
      if (this->m_data != nullptr)
      {
        str1_length = wcslen(m_data);
      }

      // get str-length of string2
      if (pStr2 != nullptr)
      {
        str2_length = wcslen(pStr2);
      }

      str_totalLength = str1_length + str2_length + 1; // + 1 for nulltermination
      if (str_totalLength == 1 || str2_length == 0) // if the right string length is 0 we can just return here
      {
        return;
      }

      // reserve bytes
      wchar_c* pBuffer = ReserveWideBytes(str_totalLength);

      // memcpy bytes from string1 into buffer and then memcpy string2 into buffer
      size_c offset = 0;
      if (str1_length > 0)
      {
        memcpy(pBuffer, this->GetCString(), str1_length);
        offset += str1_length;
      }

      if (str2_length > 0)
      {
        memcpy(pBuffer + offset, pStr2, str2_length);
        offset += str2_length;
      }

      // clear before adding the concat buffer
      Clear();

      // add null-termination
      *(pBuffer + str_totalLength) = '\0';

      m_data = pBuffer;
    }

    wchar_c CStringW::operator[](const size_c a_position) const
    {
      return CharacterAt(a_position);
    }

    wchar_c CStringW::CharacterAt(const size_c a_position) const
    {
      if (this->m_data == nullptr)
      {
        return 0;
      }
      
      // get length
      auto length = std::wcslen(this->m_data);

      if (length == 0)
        return 0;

      // increase size because strlen will not count nulltermination
      length++;

      // if length is more than a_position return 0
      if (a_position > length)
        return 0;

      // create pointer and increment by position
      wchar_c* index = this->m_data;
      index += a_position;

      return *index;
    }

    size_c CStringW::GetLength() const
    {
      if (this->m_data == nullptr)
      {
        return 0;
      }
      else
      {
        return std::wcslen(this->m_data);
      }
    }

    int32_c CStringW::Find(const wchar_c a_character) const
    {
      // loop through data
      // check if character is equal
      if (m_data == nullptr)
      {
        return -1;
      }

      wchar_c* pChar = m_data;
      int32_c pos = 0;
      while (*pChar != '\0')
      {
        if (*pChar == a_character)
        {
          return pos;
        }
        pos++;
        pChar++;
      }

      return -1;
    }

    wchar_c * CStringW::GetCString() const
    {
      return this->m_data;
    }

    CStringW::~CStringW()
    {
      this->Clear();
    }

    inline wchar_c * CStringW::ReserveWideBytes(const size_c a_size) const
    {
      return new wchar_c[a_size]();
    }

    inline void CStringW::AssignWString(const wchar_c* a_string)
    {
      Clear();

      // nullptr
      if (a_string == nullptr)
        return;
      
      // get length of a_string
      auto size = std::wcslen(a_string);

      // check size result
      if (size == 0)
        return;

      // increase size because strlen will not count nulltermination
      size++;

      // reserve bytes of length
      this->m_data = this->ReserveWideBytes(size);

      // copy a_string into m_data
      if (this->m_data != nullptr)
      {
        wmemcpy(m_data, a_string, size);
      }
    }

    inline void CStringW::Clear()
    {
      if (m_data != nullptr)
      {
        delete[] m_data;
        m_data = nullptr;
      }
    }

    inline CStringW operator+(const wchar_c * a_stringLeft, const CStringW & a_stringRight)
    {
      return a_stringRight + (a_stringLeft);
    }
  }
}