#include "stdafx.h"
#include "CMesh.h"

namespace Nully
{
	CMesh::CMesh()
	{
	}

	CMesh::~CMesh()
	{
	}

	void CMesh::Load(const std::wstring& filename)
	{

	}

	void CMesh::LoadObjFile(const std::wstring& filename)
	{

	}

	void CMesh::InitBuffers()
	{

	}

	void CMesh::ShutdownBuffers()
	{
		SafeRelease(m_pVertexBuffer);
		SafeRelease(m_pIndexBuffer);
	}
}

