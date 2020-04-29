
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
	C_STR		m_szName;
	C_STR		m_szParentName;

	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	int			m_iParentIndex;


	D3DXMATRIX  m_matWorld;
	D3DXMATRIX	m_matInverseWorld;
	D3DXMATRIX  m_Calculation;

	D3DXVECTOR3		m_vAnimScale;
	D3DXQUATERNION  m_qAnimScaleRotation;
	D3DXQUATERNION  m_qAnimRotation;
	D3DXVECTOR3		m_vAnimPos;


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