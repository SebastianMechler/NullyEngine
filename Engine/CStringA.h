#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

///@todo if a string has 10 bytes reserverd and new string with 7 characters is assigned there is no need to reallocate memory, instead use the current one

namespace Nully
{
  class CStringA
  {
  public:
    /// @brief Default constructor
    CStringA();

    /// @brief Constructor which allocates memory in size of the length from the passed c-string
    /// @param a_string Pointer to a C-String
    CStringA(const char_c* a_string);

    /// @brief Constructor which copies the string from the passed argument into new allocated memory
    /// @param a_string string object
    CStringA(const CStringA& a_string);

    /// @brief Assigns a c-string to the string-object which will also allocate new memory
    /// @param a_string Pointer to a C-String
    void operator=(const char_c* a_string);

    /// @brief Assigns the c-string from the passed argument and allocates new memory
    /// @param a_string string object
    void operator=(const CStringA& a_string);

    /// @brief Concats two string-objects
    /// @param a_string string-object
    /// @return returns a new string object which contains the concatinated string
    CStringA operator+(const CStringA& a_string) const;

    /// @brief Concats two string-objects
    /// @param a_string Pointer to a c-string
    /// @return returns a new string object which contains the concatinated string
    CStringA operator+(const char_c* a_string) const;

    /// @brief Concats another string object into the given one
    /// @param a_string string object
    void operator+=(const CStringA& a_string);

    /// @brief Gets a character from the c-string at a specific location
    /// @param a_position position from the character in the c-string
    /// @return returns the character on success and 0 on failure
    char_c operator[](const size_c a_position) const;

    /// @brief Gets a character from the c-string at a specific location
    /// @param a_position position from the character in the c-string
    /// @return returns the character on success and 0 on failure
    char_c CharacterAt(const size_c a_position) const;

    /// @brief Gets the length of the c-string
    /// @return Returns the length of the c-string without taking nulltermination in account
    size_c GetLength() const;
      
    /// @brief returns the position of first occourance from the passed value
    /// @param a_character character which will be searched for
    /// @return returns -1 if the character could not be found else a number >= 0 will be returned
    int32_c Find(const char_c a_character) const;

    /// @brief Gets the C-String
    /// @return Returns the real bytes (c-string)
    char_c* GetCString() const;

    /// @brief Destructor which will cleanup allocated memory from the heap (RAII)
    ~CStringA();    

    /// @brief Finds the index of last used character in the passed c-string.
    /// @param a_cString Nullterminated C-Style string.
    /// @param a_character Character which will be searched for.
    /// @return Returns the index of the last occourance from a_character in the c-string or -1 of not found.
    static int32_c FindLast(const char_c* a_cString, const char_c a_character);

    static void ExtractCString(const char_c* a_source, char_c* a_destination, const uint32_c a_destinationSize, const uint32_c index = 0);

  private:

    /// @brief Dynamically allocates amount of bytes
    /// @param a_size the number of bytes which will be allocated
    /// @return returns a pointer to the allocated memory
    inline char_c* ReserveBytes(const size_c a_size) const;

    /// @brief Allocates memory for the new string and copies the given data
    /// @param a_string Pointer to a c-string
    inline void AssignCString(const char_c* a_string);

    /// @brief Deallocates memory
    inline void Clear();

    char_c* m_data;
  };

  /// @brief Concats a c-string and CStringA-Object as new CStringA
  /// @param a_stringLeft Pointer to a c-string
  /// @param a_stringRight CStringA-Object
  /// @return Returns a new CStringA-Object which contains both concatinated strings
  inline CStringA operator+(const char_c* a_stringLeft, const CStringA& a_stringRight);
}