#pragma once

namespace Nully
{
  namespace Tools
  {
    template<typename T>
    CSmartPointer<T>::CSmartPointer(T* objectData)
      : m_refCount(nullptr),
        m_object(objectData)
    {
      if (m_object != nullptr)
      {
        m_refCount = new unsigned int(1);
      }
    }

    template<typename T>
    CSmartPointer<T>::~CSmartPointer()
    {
      if (m_refCount != nullptr)
      {
        (*m_refCount)--;

        if (*m_refCount == 0)
        {
          delete m_object;
          delete m_refCount;

          m_object = nullptr;
          m_refCount = nullptr;
        }
      }
    }
  }
}
