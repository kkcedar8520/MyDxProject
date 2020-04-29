#include "MaxObj.h"
bool	MaxObj::Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile)
{
	Parsing(LoadFile);
	return true;
}
void	MaxObj::Convert()
{

}
bool	MaxObj::Parsing(const TCHAR* FileName)
{
	if (!OpenStream(FileName)) { return false; }

	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s %d %d %d %d %d %d \n"),m_pString,
		&m_Scene.FirstFrame,
		&m_Scene.LastFrame,
		&m_Scene.FrameSpeed,
		&m_Scene.TickPerFrame,
		&m_Scene.iNumMaterial,
		&m_Scene.iNumMesh);
	
	int iNumSubMtl=0;
	int iNumTex;
	m_ExpMtlList.resize(m_Scene.iNumMaterial);
	for (int iMtrl = 0; iMtrl < m_Scene.iNumMaterial; iMtrl++)
	{
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer,_T("%s %d %s %d"), m_pString,
			&m_iTemp, m_pString,
			&iNumSubMtl);
		m_ExpMtlList[iMtrl].submtl.resize(iNumSubMtl);
		if (iNumSubMtl > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < iNumSubMtl; iSubMtrl++)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s %d %s %d\n"),
					m_pString,
					&iSubMtrl,
					m_pString,
					&iNumTex);
			
				m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList.resize(iNumTex);
				for (int iTex = 0; iTex < iNumTex; iTex++)
				{
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
						m_pString,
						&m_iTemp,
						&m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].iSubNo,
						m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].szTextureName);

				}

			}
		}
		else
		{
			m_ExpMtlList[iMtrl].m_MapList.resize(iNumTex);
			for (int iTex = 0; iTex < iNumTex; iTex++)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
					m_pString,
					&m_iTemp,
					&m_ExpMtlList[iMtrl].m_MapList[iTex].iSubNo,
					m_ExpMtlList[iMtrl].m_MapList[iTex].szTextureName);

			}

		}

	}
}

bool	MaxObj::OpenStream(const TCHAR* FileName)
{
	m_pStream = _tfopen(FileName, _T("rt"));
	if (m_pStream==nullptr)
	{
		return false;
	}
	return true;
}
bool	MaxObj::CloseStream() 
{
	fclose(m_pStream);
	return true;
}