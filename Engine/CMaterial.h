#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
	class CMaterial
	{
	public:
		CMaterial();
		~CMaterial();

		void Load(const std::wstring& filename);
		
		// TODO: Functions to Set Buffer Data

	private:
		class CGraphicsDX11* m_pGraphics = nullptr;

		ID3D11InputLayout* m_pInputLayout = nullptr;
		
		ID3D11VertexShader* m_pVertexShader = nullptr;
		ID3D11PixelShader* m_pPixelShader = nullptr;
	};
}

