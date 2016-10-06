#pragma once

namespace Nully
{
  namespace Tools
  {

    template<typename T>
    class CSmartPointer
    {
    public:
      CSmartPointer(T * objectData);

      ~CSmartPointer();

    private:
      unsigned int* m_refCount;
      T* m_object;

      CSmartPointer() = delete;

    };
  }
}

#include "CSmartPointer.hpp"