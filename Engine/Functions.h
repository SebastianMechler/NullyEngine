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

	bool Failed(HRESULT aResult);
}