
#pragma once
#include"JHDXCore.h"
#include"TextureMgr.h"
#include"JH_Model.h"
class Mesh
{
public:
	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	D3DXMATRIX  m_matWorld;
	Texture*	m_pTexture;
	vector<Mesh> subMesh;
	std::vector<PNCT_VERTEX> PNCTlist;
	CB_DATA     m_cbData;

public:
	Mesh();
	~Mesh();
};