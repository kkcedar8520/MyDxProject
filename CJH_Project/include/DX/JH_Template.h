#pragma once
#include"JH_DXStd.h"
namespace HTemplate {


	template<typename Child> class HTemplateMap
	{
	public:
		typedef unordered_map <int, Child*>		TemplateMap;		//Map�� ������ �����Ͽ� ������ Ʈ������ unordered_Map�� ������ ���������ʴ´�
		typedef typename TemplateMap::iterator	TemplateMapItor;	//�׷��� ��ü ���ڰ� �������� ���������� �ӵ����̰� ���̳� �ð����⵵ O(logN) O(N)
		TemplateMapItor							HItor;
		TemplateMap								HMap;
		int										m_iCurIndex;
	public:
		virtual	bool	Init();
		virtual bool	Frame();
		virtual bool	Render();
		//�ش� ���ø���ü ���λ���
		virtual bool	Release();

		virtual Child* const Getptr(int index);// ��ü �ε����� ��ü�� ���Ϲ���
		virtual Child* const Getptr(const TCHAR* szName);

		virtual int		GetID(Child*);//��ü�� �ε����� ���Ϲ���
		virtual int		GetID(const TCHAR* szName);//��ü�� �̸����� �ε����� ���Ϲ���

		virtual int		Count();//��ü ����� ��ü�� ����
		virtual bool	Delete(int Index);//�ش� �ε��� ��ü ����
		virtual bool	Delete(Child* pPoint)//�ش� ������ ��ü ����
	
	};


	template<typename Child>
	bool	HTemplateMap<Child>::Init()
	{
		m_iCurIndex = 0;
		HMap.clear();
		return true;
	}
	template<typename Child>
	bool	HTemplateMap<Child>::Frame()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor !=HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Frame();
		}
		return true;
	}
	template<typename Child>
	bool	HTemplateMap<Child>::Render()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor !=HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Render();
		}
		return true;
	}

	template<typename Child>
	bool	HTemplateMap<Child>::Release()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor != HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Release()
			else
				return false;
			delete pPoint;
		}
		HMap.clear();
		m_iCurIndex = 0;

		return true;
	}

	template<typename Child>
	Child* const HTemplateMap<Child>::Getptr(int index)
	{
		TemplateMapItor itor = HMap.find(index);
		if (itor == HMap.end())return NULL;
		Child *pPoint = (*itor).second;
		return pPoint;
	 }
	
	template < class Child >
	Child* const HTemplateMap< Child >::Getptr(const TCHAR* szName)
	{
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
			{
				return pPoint;
			}
		}
		return NULL;
	}
	template < class Child >
	int HTemplateMap< Child >::GetID(Child* pChild)
	{
		int iIndex = -1;
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (pChild == pPoint)
			{
				iIndex = (*itor).first;
				break;
			}
		}
		return iIndex;
	}
	
	template < class Child >
	int HTemplateMap< Child >::GetID(const TCHAR* szName)
	{
		int iIndex = -1;
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
			{
				iIndex = (*itor).first;
				break;
			}
		}
		return iIndex;
	}

	template < class Child >
	bool HTemplateMap< Child >::Delete(int iIndex)
	{
		Child* const pPoint = GetPtr(iIndex);
		if (pPoint)
		{
			pPoint->Release();
			TMap.erase(iIndex);
		}
		return true;
	}
	template < class Child >
	bool HTemplateMap< Child >::Delete(Child *pPoint)
	{
		if (pPoint)
		{
			pPoint->Release();
			TMap.erase(GetID(pPoint));
		}
		return true;
	}
}

