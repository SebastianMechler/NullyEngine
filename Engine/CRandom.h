#pragma once
#include "Datatypes.h"

#include <stdlib.h> // required for function: srand + rand
#include <time.h> // required for function: timeGetTime

namespace Nully
{
  namespace Tools
  {
    class CRandom
    {
    public:
      /// @brief Returns a random generated number.
      /// @param a_min: minimum value (included).
      /// @param a_max: maximum value (included).
      /// @return: returns the random generated number.
      uint32_c GetRandomNumber(const uint32_c a_min, const uint32_c a_max);

      /// @brief Returns the Singleton instance.
      static CRandom& GetInstance();

    private:

      /// @brief private & deleted Constructor + Operator overloads.
      CRandom();
      CRandom(const CRandom& other) = delete;
      CRandom operator=(const CRandom& other) = delete;
    };
  }
}


#define NULLY_RANDOM Nully::Tools::CRandom::GetInstance().GetRandomNumber
