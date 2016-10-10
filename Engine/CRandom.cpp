#include "CRandom.h"

namespace Nully
{
  namespace Tools
  {
    CRandom::CRandom()
    {
      // static variable, which will persist in all Random classes
      static bool isSeeded = false;

      if (isSeeded == false)
      {
        // Initialize the seed only once per application
        srand(static_cast<uint32_c>(time(nullptr)));
        isSeeded = true;
      }
    }

    uint32_c CRandom::GetRandomNumber(const uint32_c a_min, const uint32_c a_max)
    {
      // returns a random number between min and max
      return(rand() % (a_max - a_min + 1) + a_min);
    }

    CRandom& CRandom::GetInstance()
    {
      static CRandom rnd;
      return rnd;
    }
  }
}
