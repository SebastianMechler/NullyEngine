#pragma once
#include "stdafx.h"

namespace Nully
{
	template<typename T> void SafeRelease(T*& aInterface)
	{
		if (aInterface != nullptr)
		{
			aInterface->Release();
			aInterface = nullptr;
		}
	}

  template<typename T> void SafeDelete(T*& pObj)
  {
    if (pObj != nullptr)
    {
      delete pObj;
      pObj = nullptr;
    }
  }

	bool Failed(HRESULT aResult);
}