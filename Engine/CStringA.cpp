#include "stdafx.h"
#include "CStringA.h"

namespace Nully
{
  // Constructor 
  CStringA::CStringA()
    : m_data(nullptr)
  {
  }

  CStringA::CStringA(const char_c* a_string)
    : m_data(nullptr)
  {
    AssignCString(a_string);
  }

  // Move Constructor (lvalue) 
  CStringA::CStringA(const CStringA& a_string)
    : m_data(nullptr)
  {
    AssignCString(a_string.GetCString());
  }

  void CStringA::operator=(const char_c * a_string)
  {
    AssignCString(a_string);
  }

  void CStringA::operator=(const CStringA& a_string)
  {
    AssignCString(a_string.GetCString());
  }

  CStringA CStringA::operator+(const CStringA & a_string) const
  {
    return operator+(a_string.GetCString());
  }

  CStringA CStringA::operator+(const char_c * a_string) const
  {
    size_c str1_length = 0;
    size_c str2_length = 0;
    size_c str_totalLength = 0;
    auto pStr2 = a_string;
    CStringA concatString;

    // get str-length of string1
    if (this->m_data != nullptr)
    {
      str1_length = strlen(m_data);
    }

    // get str-length of string2
    if (pStr2 != nullptr)
    {
      str2_length = strlen(pStr2);
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
    char_c* pBuffer = concatString.ReserveBytes(str_totalLength);

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

  void CStringA::operator+=(const CStringA & a_string)
  {
    size_c str1_length = 0;
    size_c str2_length = 0;
    size_c str_totalLength = 0;
    auto pStr2 = a_string.GetCString();

    // get str-length of string1
    if (this->m_data != nullptr)
    {
      str1_length = strlen(m_data);
    }

    // get str-length of string2
    if (pStr2 != nullptr)
    {
      str2_length = strlen(pStr2);
    }

    str_totalLength = str1_length + str2_length + 1; // + 1 for nulltermination
    if (str_totalLength == 1 || str2_length == 0) // if the right string length is 0 we can just return here
    {
      return;
    }

    // reserve bytes
    char_c* pBuffer = ReserveBytes(str_totalLength);

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

  char_c CStringA::operator[](const size_c a_position) const
  {
    return CharacterAt(a_position);
  }

  char_c CStringA::CharacterAt(const size_c a_position) const
  {
    if (this->m_data == nullptr)
    {
      return 0;
    }

    // get length
    auto length = std::strlen(this->m_data);

    if (length == 0)
      return 0;

    // increase size because strlen will not count nulltermination
    length++;

    // if length is more than a_position return 0
    if (a_position > length)
      return 0;

    // create pointer and increment by position
    char_c* index = this->m_data;
    index += a_position;

    return *index;
  }

  size_c CStringA::GetLength() const
  {
    if (this->m_data == nullptr)
    {
      return 0;
    }
    else
    {
      return std::strlen(this->m_data);
    }
  }

  int32_c CStringA::Find(const char_c a_character) const
  {
    // loop through data
    // check if character is equal
    if (m_data == nullptr)
    {
      return -1;
    }

    char_c* pChar = m_data;
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

  char_c * CStringA::GetCString() const
  {
    return this->m_data;
  }

  CStringA::~CStringA()
  {
    this->Clear();
  }

  int32_c CStringA::FindLast(const char_c * a_cString, const char_c a_character)
  {
    if (a_cString == nullptr)
    {
      return -1;
    }

    int32_c strLength = strlen(a_cString);

    for (int i = strLength; i > 0; i--)
    {
      if (a_cString[i] == a_character)
      {
        return i;
      }
    }

    return -1;
  }

  void CStringA::ExtractCString(const char_c * a_source, char_c * a_destination, const uint32_c a_destinationSize, const uint32_c index)
  {
    if (a_source == nullptr || a_destination == nullptr)
    {
      return;
    }

    for (uint32_c i = 0; i < a_destinationSize; i++)
    {
      if (a_source[i + index] == '\0')
        break;

      a_destination[i] = a_source[i + index];
    }
  }

  inline char_c * CStringA::ReserveBytes(const size_c a_size) const
  {
    return new char_c[a_size]();
  }

  inline void CStringA::AssignCString(const char_c* a_string)
  {
    Clear();

    // nullptr
    if (a_string == nullptr)
      return;    

    // get length of a_string
    auto size = std::strlen(a_string);

    // check size result
    if (size == 0)
      return;

    // increase size because strlen will not count nulltermination
    size++;

    // reserve bytes of length
    this->m_data = this->ReserveBytes(size);

    // copy a_string into m_data
    if (this->m_data != nullptr)
    {
      memcpy(m_data, a_string, size);
    }
  }

  inline void CStringA::Clear()
  {
    if (m_data != nullptr)
    {
      delete[] m_data;
      m_data = nullptr;
    }
  }

  inline CStringA operator+(const char_c * a_stringLeft, const CStringA & a_stringRight)
  {
    return a_stringRight + (a_stringLeft);
  }
}