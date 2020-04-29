#pragma once
#include"JH_ShapePlane.h"
#include"JH_Input.h"
enum Stage
{
	START = 0,
	GUSTMAP,
	CloudMap,
	BOSSMap,
	MAPCOUNT,
};
class JH_Map:public JH_ShapePlane
{
public:
	DWORD	m_CorrentStage;
public:
	vector<ID3D11ShaderResourceView*> m_SrvList;
public:
	HRESULT	LoadTexture(const TCHAR* pszTexFileName);
	bool PostRender();
	bool Frame();
	
public:
	JH_Map();
	virtual ~JH_Map();
};

