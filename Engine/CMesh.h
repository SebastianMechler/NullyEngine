#pragma once
#include "stdafx.h"
#include "EngineIntern.h"

namespace Nully
{
	class CMesh
	{
	public:
		CMesh();
		~CMesh();

		void Load(const std::wstring& filename);

	private:
		void LoadObjFile(const std::wstring& filename);
		void InitBuffers();
		void ShutdownBuffers();

	private:
		ID3D11Buffer* m_pVertexBuffer = nullptr;
		ID3D11Buffer* m_pIndexBuffer = nullptr;

	};
}


