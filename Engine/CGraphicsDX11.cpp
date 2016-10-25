#include "stdafx.h"
#include "CGraphicsDX11.h"
#include "CApplication.h"
#include "CWindow.h"
#include "Functions.h"

namespace Nully
{
	CGraphicsDX11::CGraphicsDX11()
	{
	}

	CGraphicsDX11::~CGraphicsDX11()
	{
	}

	void CGraphicsDX11::Init(const SGraphicsParams& params)
	{
		HRESULT hr = S_OK;

		CWindow* pWindow = CApplication::GetWindow();
		assert(pWindow);
		HWND hwnd = pWindow->GetHandle();
		assert(hwnd);

		uint32_c width = pWindow->GetWidth();
		uint32_c height = pWindow->GetHeight();

		//---------------------------------------------
		// Setup Device and SwapChain
		//---------------------------------------------

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = TRUE;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		UINT createDeviceFlags = 0;
#if _DEBUG
		createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL outFeatureLevel;

		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlags,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&m_pDevice,
			&outFeatureLevel,
			&m_pDeviceContext);

		if (Failed(hr))
			return;

		//---------------------------------------------
		// Setup RenderTargetView
		//---------------------------------------------

		ID3D11Texture2D* pBackBuffer;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
		if (Failed(hr))
			return;

		hr = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
		if (Failed(hr))
			return;

		SafeRelease(pBackBuffer);

		//---------------------------------------------
		// Setup DepthStencil Buffer, View and State
		//---------------------------------------------

		D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilBufferDesc.Width = width;
		depthStencilBufferDesc.Height = height;
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.SampleDesc.Count = 1;
		depthStencilBufferDesc.SampleDesc.Quality = 0;
		depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		hr = m_pDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &m_pDepthStencilBuffer);
		if (Failed(hr))
			return;

		hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, &m_pDepthStencilView);
		if (Failed(hr))
			return;

		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
		depthStencilStateDesc.DepthEnable = FALSE; // TODO: Set this to TRUE when we use it
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // for transparent objs set this to ZERO. seperate draw calls. first non-transparent objs, second transparent objs.
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilStateDesc.StencilEnable = FALSE;

		hr = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, &m_pDepthStencilState);
		if (Failed(hr))
			return;

		//---------------------------------------------
		// Setup Rasterizer State
		//---------------------------------------------

		D3D11_RASTERIZER_DESC rasterizerDesc = {};

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state object.
		hr = m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
		if (Failed(hr))
			return;

		//---------------------------------------------
		// Setup Viewport
		//---------------------------------------------

		D3D11_VIEWPORT viewPort = {};
		viewPort.Height = static_cast<FLOAT>(height);
		viewPort.Width = static_cast<FLOAT>(width);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		m_pDeviceContext->RSSetViewports(1, &viewPort);
	}

	void CGraphicsDX11::Shutdown()
	{
		SafeRelease(m_pSwapChain);
		SafeRelease(m_pDevice);
		SafeRelease(m_pDeviceContext);
		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pDepthStencilBuffer);
		SafeRelease(m_pDepthStencilState);
		SafeRelease(m_pDepthStencilView);
		SafeRelease(m_pRasterizerState);
	}

	CMaterial* CGraphicsDX11::LoadMaterial(const std::wstring& file)
	{
		CMaterial* pMaterial = new CMaterial();
		pMaterial->Load(file);
		return pMaterial;
	}

}
