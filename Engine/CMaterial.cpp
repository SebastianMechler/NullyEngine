#include "stdafx.h"
#include "CMaterial.h"
#include "CGraphicsDX11.h"
#include "CApplication.h"

namespace Nully
{
	CMaterial::CMaterial()
	{
		IGraphics* pGraphicsInterface = CApplication::GetGraphics();
		assert(pGraphicsInterface);
		m_pGraphics = dynamic_cast<CGraphicsDX11*>(pGraphicsInterface);
		assert(m_pGraphics);
	}

	CMaterial::~CMaterial()
	{
		SafeRelease(m_pInputLayout);
		SafeRelease(m_pPixelShader);
		SafeRelease(m_pVertexShader);
	}

	void CMaterial::Load(const std::wstring& file)
	{
		ID3D11Device* device = m_pGraphics->GetDevice();
		HRESULT hr = S_OK;

		//---------------------------------------------
		// Load VertexShader
		//---------------------------------------------
		ID3D10Blob* pErrorBlob = nullptr;
		ID3D10Blob* pVertexShaderByteCode = nullptr;

		hr = D3DCompileFromFile(file.c_str(), NULL, NULL, "VS_Main", "vs_5_0", NULL, NULL, &pVertexShaderByteCode, &pErrorBlob);
		if (Failed(hr))
		{
			printf("%s", (const char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
			return;
		}

		hr = device->CreateVertexShader(pVertexShaderByteCode->GetBufferPointer(), pVertexShaderByteCode->GetBufferSize(), NULL, &m_pVertexShader);
		if (Failed(hr))
		{
			return;
		}

		//---------------------------------------------
		// Load PixelShader
		//---------------------------------------------
		ID3D10Blob* pPixelShaderByteCode = nullptr;

		hr = D3DCompileFromFile(file.c_str(), NULL, NULL, "PS_Main", "ps_5_0", NULL, NULL, &pPixelShaderByteCode, &pErrorBlob);
		if (Failed(hr))
		{
			printf("%s", (const char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
			return;
		}

		hr = device->CreatePixelShader(pPixelShaderByteCode->GetBufferPointer(), pPixelShaderByteCode->GetBufferSize(), NULL, &m_pPixelShader);
		if (Failed(hr))
		{
			return;
		}

		// TODO: Create Input Layout by using Shader Reflection with D3DReflect()



	}
}