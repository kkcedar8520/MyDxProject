
#include"Mesh.h"
Mesh::Mesh()
{
	

	m_iTexIndex=0;
	m_iBaseVertex = 0;
	m_iNumVertex = 0;
	m_iParentIndex = -1;


	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matInverseWorld);
	D3DXMatrixIdentity(&m_Calculation);


}

Mesh::~Mesh()
{

}