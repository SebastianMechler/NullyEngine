#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
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


#define NULLY_RANDOM Nully::CRandom::GetInstance().GetRandomNumber
