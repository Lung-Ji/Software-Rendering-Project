#include "Buffer.h"

Buffer::Buffer() :	VertexBuffer(nullptr), IndexBuffer(nullptr), VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {}
Buffer::Buffer(LPDIRECT3DDEVICE9 _GRPDEV) : Component(_GRPDEV), 
					VertexBuffer(nullptr), IndexBuffer(nullptr), VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {}
Buffer::Buffer(const Buffer& _RHS)		  : Component(_RHS), 
					VertexBuffer(_RHS.VertexBuffer), IndexBuffer(_RHS.IndexBuffer),VertexSize(_RHS.VertexSize), VertexCount(_RHS.VertexCount), 
					VertexFormat(_RHS.VertexFormat), TRICount(_RHS.TRICount), IndexSize(_RHS.IndexSize) { VertexBuffer->AddRef(); IndexBuffer->AddRef(); }
Buffer::~Buffer() {}

HRESULT Buffer::Ready_Buffer(BUFFER_TYPE _TYPE) {
	if		(_TYPE == BUFFER_TYPE::TRIANGLE	)		{ Ready_Triangle_Buffer() ;	}
	else if (_TYPE == BUFFER_TYPE::RECTANGLE)		{ Ready_Rectangle_Buffer(); }
	else if (_TYPE == BUFFER_TYPE::TEXTURE	)		{ Ready_Texture_Buffer()  ;	}
	else if (_TYPE == BUFFER_TYPE::TERRAIN	)		{ Ready_Terrain_Buffer()  ;	}

	return S_OK;
}
VOID	Buffer::Render_Buffer() {
	GRPDEV->SetStreamSource(0, VertexBuffer, 0, VertexSize);
	GRPDEV->SetFVF(VertexFormat);

	GRPDEV->SetIndices(IndexBuffer);
	GRPDEV->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VertexCount, 0, TRICount);
}

HRESULT Buffer::Ready_Triangle_Buffer() {
	VertexSize = sizeof(VTXCOL);
	VertexCount = 3;
	TRICount = 1;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { 0.f, 1.f, 0.f };
	Vertex[0].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	Vertex[1].vPosition = { 1.f, -1.f, 0.f };
	Vertex[1].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	Vertex[2].vPosition = { -1.f, -1.f, 0.f };
	Vertex[2].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	VertexBuffer->Unlock();

	INDEX32* Index = nullptr;

	IndexBuffer->Lock(0, 0, (void**)&Index, 0);

	Index[0]._0 = 0;
	Index[0]._1 = 1;
	Index[0]._2 = 2;

	IndexBuffer->Unlock();
	return S_OK;
}
HRESULT Buffer::Ready_Rectangle_Buffer() {
	VertexSize = sizeof(VTXCOL);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 1.f, 0.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	Vertex[1].vPosition = { 1.f, 1.f, 0.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	Vertex[2].vPosition = { 1.f, -1.f, 0.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	Vertex[3].vPosition = { -1.f, -1.f, 0.f };
	Vertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	VertexBuffer->Unlock();

	INDEX32* Index = nullptr;

	IndexBuffer->Lock(0, 0, (void**)&Index, 0);

	Index[0]._0 = 0;
	Index[0]._1 = 1;
	Index[0]._2 = 2;
	
	Index[1]._0 = 0;
	Index[1]._1 = 2;
	Index[1]._2 = 3;

	IndexBuffer->Unlock();
	return S_OK;
}
HRESULT Buffer::Ready_Texture_Buffer() {
	VertexSize = sizeof(VTXTEX);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_TEX;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	VTXTEX* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 1.f, 0.f };
	Vertex[0].vTexUV = { 0.f, 0.f };

	Vertex[1].vPosition = { 1.f, 1.f, 0.f };
	Vertex[1].vTexUV = { 1.f, 0.f };

	Vertex[2].vPosition = { 1.f, -1.f, 0.f };
	Vertex[2].vTexUV = { 1.f, 1.f };

	Vertex[3].vPosition = { -1.f, -1.f, 0.f };
	Vertex[3].vTexUV = { 0.f, 1.f };

	VertexBuffer->Unlock();

	INDEX32* Index = nullptr;

	IndexBuffer->Lock(0, 0, (void**)&Index, 0);

	Index[0]._0 = 0;
	Index[0]._1 = 1;
	Index[0]._2 = 2;

	Index[1]._0 = 0;
	Index[1]._1 = 2;
	Index[1]._2 = 3;

	IndexBuffer->Unlock();
	return S_OK;
}
HRESULT Buffer::Ready_Terrain_Buffer() {
	VertexSize = sizeof(VTXTEX);
	VertexCount = VTXCNTX * VTXCNTZ;
	TRICount = (VTXCNTX - 1) * (VTXCNTZ - 1) * 2;
	VertexFormat = FVF_TEX;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	VTXTEX*		Vertex	= NULL;
	INDEX32*	Index	= NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	for (INT Z = 0; Z < VTXCNTZ; ++Z) {
		for (INT X = 0; X < VTXCNTX; ++X) {

			INT INDEX = Z * VTXCNTX + X;

			Vertex[INDEX].vPosition = { (FLOAT)X, 0.f, (FLOAT)Z };
			Vertex[INDEX].vTexUV	= { ((FLOAT)(X) / (VTXCNTX-1)) * 20.f, ((FLOAT)(Z) / (VTXCNTZ - 1)) * 20.f };
		}
	}

	VertexBuffer->Unlock();
	INT INDEX = 0, TriCount = 0;
	IndexBuffer->Lock(0, 0, (void**)&Index, 0);

	for (INT Z = 0; Z < VTXCNTZ - 1; ++Z) {
		for (INT X = 0; X < VTXCNTX - 1; ++X) {

			INDEX = Z * VTXCNTX + X;

			Index[TriCount]._0 = INDEX + VTXCNTX;
			Index[TriCount]._1 = INDEX + VTXCNTX + 1;
			Index[TriCount]._2 = INDEX + 1;
			TriCount++;

			Index[TriCount]._0 = INDEX + VTXCNTX;
			Index[TriCount]._1 = INDEX + 1;
			Index[TriCount]._2 = INDEX;
			TriCount++;
		}
	}

	IndexBuffer->Unlock();
	return S_OK;
}

Buffer* Buffer::Create(LPDIRECT3DDEVICE9 _GRPDEV, BUFFER_TYPE _TYPE) {
	Buffer* BUF = new Buffer(_GRPDEV);
	if (FAILED(BUF->Ready_Buffer(_TYPE))) {
		MSG_BOX("Cannot Create Buffer.");
		Safe_Release(BUF);
		return nullptr;
	}
	return BUF;
}
Component*	Buffer::Clone() {
	return new Buffer(*this);
}
VOID		Buffer::Free() {
	Safe_Release(VertexBuffer);
	Safe_Release(IndexBuffer);

	Component::Free();
}