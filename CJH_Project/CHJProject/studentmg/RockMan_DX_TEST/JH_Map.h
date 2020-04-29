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
	ID3D11ShaderResourceView* m_pSRV_Start;
	ID3D11ShaderResourceView* m_pSRV_Gust;
	ID3D11ShaderResourceView* m_pSRV_Cloud;
	ID3D11ShaderResourceView* m_pSRV_Boss;
	DWORD	m_CorrentStage;
public:
	vector<ID3D11ShaderResourceView*> m_SrvList;
public:
	HRESULT	LoadTexture(const TCHAR* pszTexFileName);
	bool PostRender();
	bool Frame();
	static shared_ptr<JH_Map> &Get()
	{
		static shared_ptr<JH_Map> map;
		return map;
	}
public:
	JH_Map();
	virtual ~JH_Map();
};


#define I_Map JH_Map::Get()