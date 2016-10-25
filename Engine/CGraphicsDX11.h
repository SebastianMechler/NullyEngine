#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "IGraphics.h"
#include "CMaterial.h"

namespace Nully
{
	class CGraphicsDX11 : public IGraphics
	{
	public:
		CGraphicsDX11();
		virtual ~CGraphicsDX11();

		void Init(const SGraphicsParams& params) override;
		void Shutdown() override;

		CMaterial* LoadMaterial(const std::wstring& file);

		IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }
		ID3D11Device* GetDevice() { return m_pDevice; }
		ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }
		ID3D11RenderTargetView* GetRenderTargetView() { return m_pRenderTargetView; }
		ID3D11DepthStencilView* GetDepthStencilView() { return m_pDepthStencilView; }
		ID3D11DepthStencilState* GetDepthStencilState() { return m_pDepthStencilState; }
		ID3D11RasterizerState* GetRasterizerState() { return m_pRasterizerState; }

	private:
		IDXGISwapChain* m_pSwapChain = nullptr;
		ID3D11Device* m_pDevice = nullptr;
		ID3D11DeviceContext* m_pDeviceContext = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
		ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
		ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
		ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
		ID3D11RasterizerState* m_pRasterizerState = nullptr;
	};
}

