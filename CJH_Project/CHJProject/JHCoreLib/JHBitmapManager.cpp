#include "JHBitmapManager.h"



JHBitMap* JHBitmapManager::Load(const TCHAR* filename)
{
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };

	_tsplitpath_s(filename, Drive, Dir, Name, ext);

	std::wstring NameExt = Name;
	NameExt += ext;

	std::map<wstring, JHBitMap*>::iterator iter;

	iter = m_List.find(filename);
	if (iter!=m_List.end())
	{
		return (JHBitMap*)iter->second;
	}
	
	JHBitMap* pData=new JHBitMap;
	pData->m_szName = NameExt;

	wstring loadfile = Dir;
	loadfile = m_szPath + filename;

	
	pData->Init();
	if (pData->LoadBitMap(loadfile.c_str()))
	{
		m_List.insert(std::make_pair(NameExt, pData));
		return pData;
	}
	delete pData;
	return  nullptr;
	

	


}
bool JHBitmapManager::Release()
{
	std::map<wstring, JHBitMap*>::iterator iter;
	for (iter  = m_List.begin(); iter!=m_List.end(); iter++)
	{
		JHBitMap* pBitmap = (JHBitMap*)iter->second;
		pBitmap->Release();
		delete pBitmap;
	}
	m_List.clear();
	return true;

}
JHBitmapManager::JHBitmapManager()
{
	m_szPath = L"../../data/";
	m_ilndex = -1;
}


JHBitmapManager::~JHBitmapManager()
{
}
