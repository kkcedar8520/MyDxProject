
#pragma once
#include"JHDXCore.h"
#include"TextureMgr.h"
#include"JH_Model.h"

struct AnimTrack
{
	int iTick;
	D3DXVECTOR3		p;
	D3DXQUATERNION	q;
};
class Mesh
{
public:
	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;

	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_Calculation;


	Texture*	m_pTexture;
	vector<Mesh> subMesh;


	vector<AnimTrack> m_AnimTrackPos;
	vector<AnimTrack> m_AnimTrackRotate;
	vector<AnimTrack> m_AnimTrackScale;

	std::vector<PNCT_VERTEX> PNCTlist;
	CB_DATA     m_cbData;

public:
	Mesh();
	~Mesh();
};