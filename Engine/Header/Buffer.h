#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Buffer : public Component {
private:
	explicit Buffer();
	explicit Buffer(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Buffer(CONST Buffer& _RHS);
	virtual ~Buffer();

public:
	virtual		HRESULT	Ready_Buffer(BUFFER_TYPE _TYPE);
	virtual		VOID	Render_Buffer();

	_vec3* Get_BufferPos(_int iArray) { return		&pVBufferPos[iArray]; } //버퍼 pos 가져오기
public:
	HRESULT		Ready_Triangle_Buffer();
	HRESULT		Ready_Rectangle_Buffer();
	HRESULT		Ready_Texture_Buffer();
	HRESULT		Ready_Terrain_Buffer();
	HRESULT		Ready_TileLEFT_Buffer(); // 타일 옆면 비교용
	HRESULT		Ready_TileRIGHT_Buffer();//타일 옆면 비교용
	HRESULT		Ready_TileFRONT_Buffer();//타일 옆면 비교용
	HRESULT		Ready_TileBACK_Buffer(); //타일 옆면 비교용
	HRESULT		Ready_Tile_Buffer(); // 타일 추가 윗면 비교용
	HRESULT		Ready_Cube_Buffer(); // 큐브타일 추가
protected:
	LPDIRECT3DVERTEXBUFFER9		VertexBuffer;
	LPDIRECT3DINDEXBUFFER9		IndexBuffer;

	ULONG						VertexSize;
	ULONG						VertexCount;
	ULONG						VertexFormat;
	ULONG						TRICount;

	ULONG						IndexSize;
	D3DFORMAT					IndexFormat;


	_vec3*						pVBufferPos; //버퍼 인덱스 담는 용도
public:
	static		Buffer* Create(LPDIRECT3DDEVICE9 _GRPDEV, BUFFER_TYPE _TYPE);
	virtual		Component* Clone();

protected:
	virtual		void	Free();
};

END