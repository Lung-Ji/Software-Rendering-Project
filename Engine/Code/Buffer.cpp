#include "Buffer.h"

Buffer::Buffer() :	VertexBuffer(nullptr), IndexBuffer(nullptr), pVBufferPos(nullptr), VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {}
Buffer::Buffer(LPDIRECT3DDEVICE9 _GRPDEV) : Component(_GRPDEV), 
					VertexBuffer(nullptr), IndexBuffer(nullptr), pVBufferPos(nullptr),  VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {}
Buffer::Buffer(const Buffer& _RHS)		  : Component(_RHS), 
					VertexBuffer(_RHS.VertexBuffer), IndexBuffer(_RHS.IndexBuffer),VertexSize(_RHS.VertexSize), VertexCount(_RHS.VertexCount), 
					VertexFormat(_RHS.VertexFormat), TRICount(_RHS.TRICount), IndexSize(_RHS.IndexSize),pVBufferPos(_RHS.pVBufferPos) { VertexBuffer->AddRef(); IndexBuffer->AddRef(); }
Buffer::~Buffer() {}

HRESULT Buffer::Ready_Buffer(BUFFER_TYPE _TYPE) {
	if		(_TYPE == BUFFER_TYPE::TRIANGLE	)		{ Ready_Triangle_Buffer() ;	}
	else if (_TYPE == BUFFER_TYPE::RECTANGLE)		{ Ready_Rectangle_Buffer(); }
	else if (_TYPE == BUFFER_TYPE::TEXTURE	)		{ Ready_Texture_Buffer()  ;	}
	else if (_TYPE == BUFFER_TYPE::TERRAIN	)		{ Ready_Terrain_Buffer()  ;	}
    else if (_TYPE == BUFFER_TYPE::TILE)			{ Ready_Tile_Buffer()	  ; }
    else if (_TYPE == BUFFER_TYPE::CUBE)			{ Ready_Cube_Buffer()	  ; }
	else if (_TYPE == BUFFER_TYPE::TILEFRONT)		{ Ready_TileFRONT_Buffer(); }
	else if (_TYPE == BUFFER_TYPE::TILELEFT)		{ Ready_TileLEFT_Buffer(); }
	else if (_TYPE == BUFFER_TYPE::TILERIGHT)		{ Ready_TileRIGHT_Buffer(); }
	else if (_TYPE == BUFFER_TYPE::TILEBACK)		{ Ready_TileBACK_Buffer(); }
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
	pVBufferPos = new _vec3[VertexCount];
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
			pVBufferPos[INDEX] = Vertex[INDEX].vPosition;
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
HRESULT Buffer::Ready_TileRIGHT_Buffer()
{
	VertexSize = sizeof(VTXCOL);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	pVBufferPos = new _vec3[VertexCount];
	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);


	Vertex[0].vPosition = { 1.f, 1.f, -1.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[0] = Vertex[0].vPosition;
	Vertex[1].vPosition = { 1.f, 1.f, 1.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[1] = Vertex[1].vPosition;
	Vertex[2].vPosition = { 1.f, -1.f, 1.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[2] = Vertex[2].vPosition;
	Vertex[3].vPosition = { 1.f, -1.f, -1.f };
	Vertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[3] = Vertex[3].vPosition;
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
HRESULT Buffer::Ready_TileFRONT_Buffer()
{
	VertexSize = sizeof(VTXCOL);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	pVBufferPos = new _vec3[VertexCount];
	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 1.f, 1.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[0] = Vertex[0].vPosition;
	Vertex[1].vPosition = { 1.f, 1.f, 1.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[1] = Vertex[1].vPosition;
	Vertex[2].vPosition = { 1.f, -1.f, 1.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[2] = Vertex[2].vPosition;
	Vertex[3].vPosition = { -1.f, -1.f, 1.f };
	Vertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[3] = Vertex[3].vPosition;
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
HRESULT Buffer::Ready_TileBACK_Buffer()
{
	VertexSize = sizeof(VTXCOL);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	pVBufferPos = new _vec3[VertexCount];
	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 1.f, -1.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[0] = Vertex[0].vPosition;
	Vertex[1].vPosition = { 1.f, 1.f, -1.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[1] = Vertex[1].vPosition;
	Vertex[2].vPosition = { 1.f, -1.f, -1.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[2] = Vertex[2].vPosition;
	Vertex[3].vPosition = { -1.f, -1.f, -1.f };
	Vertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[3] = Vertex[3].vPosition;
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
HRESULT Buffer::Ready_TileLEFT_Buffer()
{
	VertexSize = sizeof(VTXCOL);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_COL;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	pVBufferPos = new _vec3[VertexCount];
	VTXCOL* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 1.f, -1.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[0] = Vertex[0].vPosition;
	Vertex[1].vPosition = { -1.f, 1.f, 1.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[1] = Vertex[1].vPosition;
	Vertex[2].vPosition = { -1.f, -1.f, 1.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[2] = Vertex[2].vPosition;
	Vertex[3].vPosition = { -1.f, -1.f, -1.f };
	Vertex[3].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pVBufferPos[3] = Vertex[3].vPosition;
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
HRESULT Buffer::Ready_Tile_Buffer()
{
	VertexSize = sizeof(VTXCUBE);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_CUBE;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	pVBufferPos = new _vec3[VertexCount];
	VTXCUBE* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);


	Vertex[0].vPosition = { -1.f, 0.f, 1.f };
	Vertex[0].vTexUV = {0,0,1};

	Vertex[1].vPosition = { 1.f, 0.f, 1.f };
	Vertex[1].vTexUV = {1,0,0};

	Vertex[2].vPosition = { 1.f, 0.f, -1.f };
	Vertex[2].vTexUV = { 1,0,0 };

	Vertex[3].vPosition = { -1.f, 0.f, -1.f };
	Vertex[3].vTexUV = { 0,0,0 };
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
HRESULT Buffer::Ready_Cube_Buffer()
{
	VertexSize = sizeof(VTXCUBE);
	VertexCount = 8;
	TRICount = 12;
	VertexFormat = FVF_CUBE;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;


	VTXCUBE* pVertex = NULL;

	// &pVertex : 버텍스버퍼에 보관된 버텍스 중 첫 번째 버텍스의 주소를 얻어옴
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;

	VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 1.f, -1.f };
	pVertex[0].vTexUV = pVertex[0].vPosition;

	pVertex[1].vPosition = { 1.f, 1.f, -1.f };
	pVertex[1].vTexUV = pVertex[1].vPosition;

	pVertex[2].vPosition = { 1.f, -1.f, -1.f };
	pVertex[2].vTexUV = pVertex[2].vPosition;

	pVertex[3].vPosition = { -1.f, -1.f, -1.f };
	pVertex[3].vTexUV = pVertex[3].vPosition;

	pVertex[4].vPosition = { -1.f, 1.f, 1.f };
	pVertex[4].vTexUV = pVertex[4].vPosition;

	pVertex[5].vPosition = { 1.f, 1.f, 1.f };
	pVertex[5].vTexUV = pVertex[5].vPosition;

	pVertex[6].vPosition = { 1.f, -1.f, 1.f };
	pVertex[6].vTexUV = pVertex[6].vPosition;

	pVertex[7].vPosition = { -1.f, -1.f, 1.f };
	pVertex[7].vTexUV = pVertex[7].vPosition;

	VertexBuffer->Unlock();

	INDEX32* pIndex = nullptr;

	IndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	// X+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	// X+
	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// X-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	// X-
	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// Y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	// Y+
	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// Y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	// Y-
	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// Z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	// Z+
	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// Z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	// Z-
	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

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

	if(false == CLONE)
		Safe_Delete_Array(pVBufferPos);
		
	Safe_Release(VertexBuffer);
	Safe_Release(IndexBuffer);

	Component::Free();
}