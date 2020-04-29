#pragma once
#include"JH_Model.h"
#include"AsePaser.h"



class xAseObj:public JH_Model
{
public:
	vector<PNCT_VERTEX> m_PNCTBuffer;

	vector<Mesh> m_MeshList;

	AsePaser m_Parser;
public:
	bool	Load(ID3D11Device* pdvice,ID3D11DeviceContext* pContext,const TCHAR* LoadFile);
	void	Convert();
public:
	HRESULT CreateVertexData()override;
	HRESULT CreateIndexData()override;
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	xAseObj();
	virtual ~xAseObj();
};

