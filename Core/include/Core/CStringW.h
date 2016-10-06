#pragma once

#include <iostream>

#include "Datatypes.h"

///@todo if a string has 10 bytes reserverd and new string with 7 characters is assigned there is no need to reallocate memory, instead use the current one

namespace Nully
{
  namespace Tools
  {
    class CStringW
    {
    public:
      /// @brief Default constructor
      CStringW();

      /// @brief Constructor which allocates memory in size of the length from the passed c-string
      /// @param a_string Pointer to a C-String
      CStringW(const wchar_c* a_string);

      /// @brief Constructor which copies the string from the passed argument into new allocated memory
      /// @param a_string string object
      CStringW(const CStringW& a_string);

      /// @brief Assigns a c-string to the string-object which will also allocate new memory
      /// @param a_string Pointer to a C-String
      void operator=(const wchar_c* a_string);

      /// @brief Assigns the c-string from the passed argument and allocates new memory
      /// @param a_string string object
      void operator=(const CStringW& a_string);

      /// @brief Concats two string-objects
      /// @param a_string string-object
      /// @return returns a new string object which contains the concatinated string
      CStringW operator+(const CStringW& a_string) const;

      /// @brief Concats two string-objects
      /// @param a_string Pointer to a c-string
      /// @return returns a new string object which contains the concatinated string
      CStringW operator+(const wchar_c* a_string) const;

      /// @brief Concats another string object into the given one
      /// @param a_string string object
      void operator+=(const CStringW& a_string);

      /// @brief Gets a character from the c-string at a specific location
      /// @param a_position position from the character in the c-string
      /// @return returns the character on success and 0 on failure
      wchar_c operator[](const size_c a_position) const;

      /// @brief Gets a character from the c-string at a specific location
      /// @param a_position position from the character in the c-string
      /// @return returns the character on success and 0 on failure
      wchar_c CharacterAt(const size_c a_position) const;

      /// @brief Gets the length of the c-string
      /// @return Returns the length of the c-string without taking nulltermination in account
      size_c GetLength() const;

      /// @brief returns the position of first occourance from the passed value
      /// @param a_character character which will be searched for
      /// @return returns -1 if the character could not be found else a number >= 0 will be returned
      int32_c Find(const wchar_c a_character) const;

      /// @brief Gets the C-String
      /// @return Returns the real bytes (c-string)
      wchar_c* GetCString() const;

      /// @Brief Destructor which will cleanup allocated memory from the heap (RAII)
      ~CStringW();

    private:

      /// @brief Dynamically allocates amount of bytes
      /// @param a_size the number of wide-bytes (16-bit) which will be allocated
      /// @return returns a pointer to the allocated memory
      inline wchar_c* ReserveWideBytes(const size_c a_size) const;

      /// @brief Allocates memory for the new string and copies the given data
      /// @param a_string Pointer to a c-string
      inline void AssignWString(const wchar_c* a_string);

      /// @brief Deallocates memory
      inline void Clear();

      wchar_c* m_data;
    };

    /// @brief Concats a c-string and CString-Object as new CString
    /// @param a_stringLeft Pointer to a c-string
    /// @param a_stringRight CString-Object
    /// @return Returns a new CString-Object which contains both concatinated strings
    inline CStringW operator+(const wchar_c* a_stringLeft, const CStringW& a_stringRight);
  }
}