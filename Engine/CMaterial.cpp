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

	void CMaterial::Load(const std::wstring& filename)
	{
		ID3D11Device* device = m_pGraphics->GetDevice();
		HRESULT hr = S_OK;

		//---------------------------------------------
		// Load and Create VertexShader
		//---------------------------------------------
		ID3D10Blob* pErrorBlob = nullptr;
		ID3D10Blob* pVertexShaderByteCode = nullptr;

		hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "VS_Main", "vs_5_0", NULL, NULL, &pVertexShaderByteCode, &pErrorBlob);
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
		// Load and Create PixelShader
		//---------------------------------------------
		ID3D10Blob* pPixelShaderByteCode = nullptr;

		hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "PS_Main", "ps_5_0", NULL, NULL, &pPixelShaderByteCode, &pErrorBlob);
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

		//---------------------------------------------
		// Create InputLayout by using ShaderReflection
		//---------------------------------------------
		ID3D11ShaderReflection* pVSReflection = nullptr;
		hr = D3DReflect(pVertexShaderByteCode->GetBufferPointer(),
			pVertexShaderByteCode->GetBufferSize(),
			__uuidof(ID3D11ShaderReflection),
			reinterpret_cast<void**>(&pVSReflection));
		if (Failed(hr))
			return;

		D3D11_SHADER_DESC shaderDesc;
		hr = pVSReflection->GetDesc(&shaderDesc);
		if (Failed(hr))
			return;

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
		for (uint32_c i = 0; i < shaderDesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			hr = pVSReflection->GetInputParameterDesc(i, &paramDesc);
			if (Failed(hr))
				return;

			D3D11_INPUT_ELEMENT_DESC inElemDesc = {};
			inElemDesc.SemanticIndex = paramDesc.SemanticIndex;
			inElemDesc.SemanticName = paramDesc.SemanticName;
			inElemDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;


			// TODO: Get these values from a shader metadata file or param
			inElemDesc.InputSlot = 0;
			inElemDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inElemDesc.InstanceDataStepRate = 0;


			// Determine DXGI Format
			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inElemDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inElemDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inElemDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inElemDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inElemDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inElemDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inElemDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			inputLayoutDesc.push_back(inElemDesc);
		}

		hr = device->CreateInputLayout(inputLayoutDesc.data(),
			inputLayoutDesc.size(),
			pVertexShaderByteCode->GetBufferPointer(),
			pVertexShaderByteCode->GetBufferSize(),
			&m_pInputLayout);
		if (Failed(hr))
			return;

		//---------------------------------------------
		// Clean up
		//---------------------------------------------
		SafeRelease(pVSReflection);
		SafeRelease(pVertexShaderByteCode);
		SafeRelease(pPixelShaderByteCode);
	}
}