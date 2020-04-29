#include "GlobalExp.h"

struct DescendingDateSort
{
	bool operator()(HTri& rpStart, HTri& rpEnd)
	{
		return rpStart.iSubIndex < rpEnd.iSubIndex;
	}
};
void GlobalExp::DumpQuat(Quat& p1, Quat& p2)
{
	p1.x = p2.x;
	p1.y = p2.z;
	p1.z = p2.y;
	p1.w = p2.w;
}
void GlobalExp::DumpPoint3(Point3& p1, Point3& p2)
{
	p1.x = p2.x;
	p1.y = p2.z;
	p1.z = p2.y;
	
	
}
void GlobalExp::TransDXMatrix(Matrix3& m, D3D_MATRIX& dm)
{
	Point3 row;
	row=m.GetRow(0);
	dm._11 = row.x; dm._12 = row.z; dm._13 = row.y;
	row = m.GetRow(1);
	dm._21 = row.x; dm._22 = row.z; dm._23 = row.y;
	row = m.GetRow(2);
	dm._31 = row.x; dm._32 = row.z; dm._33 = row.y;
	row = m.GetRow(3);
	dm._41 = row.x; dm._42 = row.z; dm._43 = row.y;

	dm._14 = 0; dm._24 = 0; dm._34 = 0; dm._44 = 1;

	
}
void GlobalExp::AddObject(INode* pNode)
{	
	ObjectState OS = pNode->EvalWorldState(m_Interval.Start());
	
	if (OS.obj!=nullptr)
	{
		SClass_ID id = OS.obj->SuperClassID();
		switch (id)
		{
		case GEOMOBJECT_CLASS_ID:
		case HELPER_CLASS_ID:
		{
			m_ObjList.push_back(pNode);
		}
		default:
			break;
		}
	}

	return;
}
void GlobalExp::AddMaterial(INode* pNode)
{
	Mtl* pMtl = pNode->GetMtl();

	
	if (pMtl!=nullptr)
	{
		bool bAdd = true;
		for ( int iMtl = 0;  iMtl < m_MtlList.size();  iMtl++)
		{
			if (m_MtlList[iMtl]==pMtl)
			{
				bAdd = false;
			}
		}
		if (bAdd)
		{
			m_MtlList.push_back(pMtl);
		}
	}

	return;
}
void GlobalExp::PreProcess(INode* pNode)
{
	if (pNode == nullptr) { return; }

	AddMaterial(pNode);
	AddObject(pNode);
	
	int iNumChild = pNode->NumberOfChildren();
	for (int iChild = 0;  iChild < iNumChild; iChild++)
	{
		PreProcess(pNode->GetChildNode(iChild));
	}
}
void GlobalExp::GetTexture(Mtl* pMtl, Mtrl& JMtrl)
{
	int iNumSubMap = pMtl->NumSubTexmaps();
	for ( int iSubMap = 0;  iSubMap < iNumSubMap;  iSubMap++)
	{
		//SUBNO ������� �ٵ��� EX)DIFFUSE,SPECULAR ���..
		Texmap* tex = pMtl->GetSubTexmap(iSubMap);
		if (tex!=nullptr)
		{
			Class_ID id = tex->ClassID();

			if (id== Class_ID(BMTEX_CLASS_ID,0x00))
			{
				MapInfo Minfo;
				BitmapTex* pBitTex = (BitmapTex*)tex;
				MSTR MapName;
				MapName =pBitTex->GetMapName();

				MSTR szDir, szName;

				SplitPathFile(MapName, &szDir,&szName);

				Minfo.szTextureName = szName;
				Minfo.iSubNo = iSubMap;
				JMtrl.m_MapList.push_back(Minfo);
			}
		}
	}
}
// Max�� �θ𰡾�� ������ �θ� ��尡 �ִ�.

bool GlobalExp::Convert()
{
	int iNumMtl = m_MtlList.size();
	m_ExpMtlList.resize(iNumMtl);
	for ( int iMtl  = 0; iMtl  < iNumMtl; iMtl ++)
	{
		int iNumSubMtl = m_MtlList[iMtl]->NumSubMtls();
		if (iNumSubMtl>0)
		{
			m_ExpMtlList[iMtl].submtl.resize(iNumSubMtl);
			for (int iSubMtl = 0; iSubMtl < iNumSubMtl; iSubMtl++)
			{
				Mtl* pSubMtl = m_MtlList[iMtl]->GetSubMtl(iSubMtl);
				GetTexture(pSubMtl, m_ExpMtlList[iMtl].submtl[iSubMtl]);
			}

		}
		else
		{
			GetTexture(m_MtlList[iMtl], m_ExpMtlList[iMtl]);
		}
		
	}
	m_ExpObject.resize(m_ObjList.size());


	for ( int iObj = 0; iObj < m_ExpObject.size(); iObj++)
	{
		m_ExpObject[iObj].m_szName = m_ObjList[iObj]->GetName();
		
		Mtl* Src = m_ObjList[iObj]->GetMtl();
		for (int iMtl = 0; iMtl < m_MtlList.size(); iMtl++)
		{
			m_ExpObject[iObj].m_iRef = -1;
			if (Src == m_MtlList[iMtl])
			{
				m_ExpObject[iObj].m_iRef = iMtl;

			}
		}
		INode* pParent = m_ObjList[iObj]->GetParentNode();
		// �θ��尡 ��� 3dmax ������ ������ �θ��带 ����� ���� �װŸ� �����ϴ� �Լ��� isRootNode�̴�.
		if (pParent !=nullptr&&!pParent->IsRootNode())
		{
			m_ExpObject[iObj].m_szParentName = pParent->GetName();
		}
		Matrix3 matWorld = m_ObjList[iObj]->GetNodeTM(m_Interval.Start());
		// Matrix3 float[4][3] ������ �Ǿ��ֱ� ������ D3DXMatrix ������ �°� ��ȯ�Ѵ�.
		TransDXMatrix(matWorld,m_ExpObject[iObj].m_matWorld);
		GetMesh(m_ObjList[iObj],&m_ExpObject[iObj]);
		
		BOOL bPosAnim, bRotAnim, bSclAnim;
		bPosAnim =bRotAnim=bSclAnim=FALSE;
		if (CheckForAnimation(m_ObjList[iObj], bPosAnim, bRotAnim, bSclAnim))
		{
			if (bPosAnim)
			{
				DumpPosSample(m_ObjList[iObj],&m_ExpObject[iObj]);
			}
			if (bRotAnim)
			{
				DumpRotSample(m_ObjList[iObj], &m_ExpObject[iObj]);
			}
			if (bSclAnim)
			{
				DumpSclSample(m_ObjList[iObj], &m_ExpObject[iObj]);
			}
		}
	}


	return true;
}
void GlobalExp::DumpPosSample(INode* pNode, HMesh* pMesh)
{
	
	for ( int iTick = m_Interval.Start(); iTick < m_Interval.End(); iTick+=GetTicksPerFrame())
	{
		AffineParts ap;
		AnimTrack Track;
		ZeroMemory(&Track, sizeof(AnimTrack));
		GetDecompAffine(pNode, iTick, &ap);

		Track.iTick = iTick;
		DumpPoint3(Track.p,ap.t);

		pMesh->m_AnimTrackPos.push_back(Track);
	}

}
void  GlobalExp::DumpRotSample(INode* pNode, HMesh* pMesh)
{
	for (int iTick = m_Interval.Start(); iTick < m_Interval.End(); iTick += GetTicksPerFrame())
	{
		AffineParts ap;
		AnimTrack Track;
		ZeroMemory(&Track, sizeof(AnimTrack));
		GetDecompAffine(pNode, iTick, &ap);

		Track.iTick = iTick;
		DumpQuat(Track.q, ap.q);


		pMesh->m_AnimTrackRotate.push_back(Track);
	}
}
void  GlobalExp::DumpSclSample(INode* pNode, HMesh* pMesh)
{
	for (int iTick = m_Interval.Start(); iTick < m_Interval.End(); iTick += GetTicksPerFrame())
	{
		AffineParts ap;
		AnimTrack Track;
		ZeroMemory(&Track, sizeof(AnimTrack));
		GetDecompAffine(pNode, iTick, &ap);

		Track.iTick = iTick;
		DumpPoint3(Track.p, ap.k);
		DumpQuat(Track.q, ap.u);
		
		

		pMesh->m_AnimTrackScale.push_back(Track);
	}
}
bool GlobalExp::CheckForAnimation(INode* pNode, BOOL& bPosAnim, BOOL& bRotAnim, BOOL& bSclAnim)
{
	TimeValue TicksPerFrame = GetTicksPerFrame();
	TimeValue start = m_Interval.Start()+TicksPerFrame;
	TimeValue end	= m_Interval.End();

	AffineParts ap;

	GetDecompAffine(pNode,m_Interval.Start(),&ap);

	Point3 firstScale,firstPos, firstRotAxis, fristScaleAxis,fAxis;
	float  firstRotAngle, firtScaleAngle,fAngle;

	firstPos = ap.t;
	AngAxisFromQ(ap.q,&firstRotAngle, firstRotAxis);
	AngAxisFromQ(ap.u, &firtScaleAngle, fristScaleAxis);

	firstScale = ap.k;
	for (int iTick = start; iTick < end; iTick+=TicksPerFrame)
	{
		GetDecompAffine(pNode, iTick, &ap);
		if (!EqualPoint3(firstPos,ap.t))
		{
			bPosAnim = TRUE;

		}
		AngAxisFromQ(ap.q, &fAngle, fAxis);
		if (!EqualPoint3(fAxis, firstRotAxis))
		{
			bRotAnim = TRUE;
		}

		if (!EqualPoint3(ap.k, firstScale))
		{
			bSclAnim = TRUE;
		}
	}
	return bPosAnim | bRotAnim | bSclAnim;
}
void GlobalExp::GetDecompAffine(INode* pNode, TimeValue t,AffineParts* ap)
{
	Matrix3 tm=pNode->GetNodeTM(t)*Inverse(pNode->GetParentTM(t));

	::decomp_affine(tm,ap);
		
}
bool GlobalExp::TMNegParity(Matrix3 &m)
{
	Point3 vRow = CrossProd(m.GetRow(0), m.GetRow(1));
	return (DotProd(vRow, m.GetRow(2)) < 0.0) ? 1 : 0;
}
bool GlobalExp::GetMesh(INode* pNode, HMesh* hmesh)
{							
	
	ObjectState OS = pNode->EvalWorldState(m_Interval.Start());// �ش� ����� ����ƽ�� ���� ����

	if (OS.obj == nullptr | OS.obj->SuperClassID() != GEOMOBJECT_CLASS_ID)
	{
		return false;
	}
	
	Matrix3 tm = pNode->GetObjTMAfterWSM(m_Interval.Start());//�ش� ������Ʈ�� �������� ���� ��Ʈ������ ����
															//������ǥ�� ������ǥ�̸� ��������̰� ������ǥ�̸� ��������̴�. 
															//	�׷��� ��İ� ��ǥ�� ���ϸ� �������� ���� �׻� ������ǥ�� �ȴ�
															//max�� dx�� ��ġ �����̹Ƿ� ��ǥ*����� �ƴ� ���*��ǥ ���°� �Ǿ���Ѵ�.
	Matrix3 pInverse = Inverse(pNode->GetNodeTM(m_Interval.Start()));// ��������� ������� �ٽð����ش�
	
	BOOL negScale = TMNegParity(tm);
	int i0, i1, i2;
	if (negScale) {
		i0 = 2;	i1 = 0;	i2 = 1;
	}
	else {
		i0 = 0;	i1 = 2;	i2 = 1;
	}



	BOOL NeedDel;
	TriObject* tri = GetTriObjectFromNode(pNode, m_Interval.Start(), NeedDel);

	Mesh mesh = tri->GetMesh();
	hmesh->m_TriList.resize(mesh.numFaces);

	TransDXMatrix(pNode->GetNodeTM(m_Interval.Start()), hmesh->m_matWorld);

	for (int  iFace = 0; iFace < mesh.numFaces; iFace++)
	{
		hmesh->m_TriList[iFace].iSubIndex=mesh.faces[iFace].getMatID();// SubMTLID;
		Point3 v = tm* pInverse*mesh.verts[mesh.faces[iFace].v[i0]];
		DumpPoint3(hmesh->m_TriList[iFace].v[0].p, v);  // ���� �ٸ��⶧���� �ð�������� �����ֱ����ؼ� �ε��� ��ȣ�� ��ȯ
		v= tm* pInverse*mesh.verts[mesh.faces[iFace].v[i1]];
		DumpPoint3(hmesh->m_TriList[iFace].v[1].p, v);
		v = tm* pInverse*mesh.verts[mesh.faces[iFace].v[i2]];
		DumpPoint3(hmesh->m_TriList[iFace].v[2].p, v);


		if (mesh.getNumTVerts()>0)
		{
			hmesh->m_TriList[iFace].v[0].t.x = mesh.tVerts[mesh.tvFace[iFace].t[i0]].x;
			hmesh->m_TriList[iFace].v[0].t.y = 1-mesh.tVerts[mesh.tvFace[iFace].t[i0]].y;
			hmesh->m_TriList[iFace].v[0].t.x = mesh.tVerts[mesh.tvFace[iFace].t[i1]].x;
			hmesh->m_TriList[iFace].v[0].t.y = 1 - mesh.tVerts[mesh.tvFace[iFace].t[i1]].y;
			hmesh->m_TriList[iFace].v[0].t.x = mesh.tVerts[mesh.tvFace[iFace].t[i2]].x;
			hmesh->m_TriList[iFace].v[0].t.y = 1 - mesh.tVerts[mesh.tvFace[iFace].t[i2]].y;

		}
		
		if (mesh.numCVerts > 0)
		{
			hmesh->m_TriList[iFace].v[0].c.x = mesh.vertCol[mesh.vcFace->t[i0]].x;
			hmesh->m_TriList[iFace].v[0].c.y = mesh.vertCol[mesh.vcFace->t[i0]].y;
			hmesh->m_TriList[iFace].v[0].c.z = mesh.vertCol[mesh.vcFace->t[i0]].z;
			hmesh->m_TriList[iFace].v[0].c.w = 1.0f;
			 											 
			hmesh->m_TriList[iFace].v[1].c.x = mesh.vertCol[mesh.vcFace->t[i1]].x;
			hmesh->m_TriList[iFace].v[1].c.y = mesh.vertCol[mesh.vcFace->t[i1]].y;
			hmesh->m_TriList[iFace].v[1].c.z = mesh.vertCol[mesh.vcFace->t[i1]].z;
			hmesh->m_TriList[iFace].v[1].c.w = 1.0f;
															 
			hmesh->m_TriList[iFace].v[2].c.x = mesh.vertCol[mesh.vcFace->t[i2]].x;
			hmesh->m_TriList[iFace].v[2].c.y = mesh.vertCol[mesh.vcFace->t[i2]].y;
			hmesh->m_TriList[iFace].v[2].c.z = mesh.vertCol[mesh.vcFace->t[i2]].z;
			hmesh->m_TriList[iFace].v[2].c.w = 1.0f;
		}
		else
		{
			hmesh->m_TriList[iFace].v[0].c = { 1,1,1,1 };
			hmesh->m_TriList[iFace].v[1].c = { 1,1,1,1 };
			hmesh->m_TriList[iFace].v[2].c = { 1,1,1,1 };
		}

		mesh.buildNormals();
		
		int  vert = mesh.faces[iFace].getVert(i0);
		Point3 vn = GetVertexNormal(&mesh, iFace, mesh.getRVertPtr(vert));
		DumpPoint3(hmesh->m_TriList[iFace].v[0].n, vn);

		vert = mesh.faces[iFace].getVert(i1);
		vn = GetVertexNormal(&mesh, iFace, mesh.getRVertPtr(vert));
		DumpPoint3(hmesh->m_TriList[iFace].v[1].n, vn);

		vert = mesh.faces[iFace].getVert(i2);
		vn = GetVertexNormal(&mesh, iFace, mesh.getRVertPtr(vert));

		DumpPoint3(hmesh->m_TriList[iFace].v[2].n, vn);

		
	}

	if (NeedDel==TRUE)
	{
		delete tri;
	}
	return true;
}
Point3	GlobalExp::GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv)
{
	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;//�⺻���� 0�̹Ƿ� 0�̸� ������������
	int NumNormal = rv->rFlags&NORCT_MASK;//���ؽ� �븻���� Ȯ��
	Point3 VertexNorm;


	if (rv->rFlags&SPECIFIED_NORMAL)
	{
		VertexNorm = rv->rn.getNormal();
	}
	else if (NumNormal&& smGroup)
	{
		if (NumNormal == 1)// ���ؽ� �븻�� �ϳ���� �׷��� �ǹ̰� �����Ƿ� �׳� ��ȯ�Ѵ�.
		{
			VertexNorm = rv->rn.getNormal();
		}
		else
		{
			// If two or more vertices are there you need to step through them
		// and find the vertex with the same smoothing group as the current face.
		// You will find multiple normals in the ern member.
			for (int i = 0; i < NumNormal; i++) {
				if (rv->ern[i].getSmGroup() & smGroup) {
					VertexNorm = rv->ern[i].getNormal();
				}
			}
		}
	}
	return VertexNorm;

}
TriObject* GlobalExp::GetTriObjectFromNode(INode* pNode, int Tick, BOOL& NeedDel)
{
	Object* obj = pNode->EvalWorldState(Tick).obj;
	if(!obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID,0)))
	{
		return nullptr;
	}
	TriObject* tri = (TriObject*)obj->ConvertToType(Tick, Class_ID(TRIOBJ_CLASS_ID, 0));
	//Maya�� �簢���� �⺻ �𵨸����� ����ϱ� ������ �ﰢ�� ���°� ����� ���� ���� ��찡 �ִ�.
	// �׷� ��� ���� �Ҵ��Ͽ� ����� ������ ���� ���� ������ �̸� ��������Ѵ�
	
	if (obj != tri) { NeedDel = TRUE; } 
	
	return tri;
}
bool GlobalExp::Init(Interface* MaxInterface)
{
	m_pMax = MaxInterface;
	m_pRootNode = m_pMax->GetRootNode();
	m_Interval = m_pMax->GetAnimRange();
	PreProcess(m_pRootNode);

	Convert();
	ZeroMemory(&m_Scene, sizeof(SCENEINFO));
	m_Scene.FirstFrame = m_Interval.Start() / GetTicksPerFrame();
	m_Scene.LastFrame = m_Interval.End() / GetTicksPerFrame();
	m_Scene.FrameSpeed = GetFrameRate();
	m_Scene.TickPerFrame = GetTicksPerFrame();
	m_Scene.iNumMaterial = m_MtlList.size();
	m_Scene.iNumMesh = m_ObjList.size();
	return true;
}
bool GlobalExp::Exporter(const MCHAR *name)
{
	FILE* fp;

	fp = _tfopen(name, _T("wt"));

	
	_ftprintf(fp, _T("%s %d %d %d %d %d %d\n"),L"Scene",
		m_Scene.FirstFrame,
		m_Scene.LastFrame,
		m_Scene.FrameSpeed,
		m_Scene.TickPerFrame,
		m_Scene.iNumMaterial,
		m_Scene.iNumMesh);

	for ( int iMtrl = 0;  iMtrl < m_ExpMtlList.size();  iMtrl++)
	{
		_ftprintf(fp, _T("%s %d %s %d \n"), 
			L"MATERIAL",
			iMtrl, L"SUBMATERIALNUM", 
			m_ExpMtlList[iMtrl].submtl.size());
		int iNumSub=m_ExpMtlList[iMtrl].submtl.size();
		if (iNumSub>0)
		{
			for (int iSubMtrl = 0; iSubMtrl < iNumSub; iSubMtrl++)
			{
				int iNumTex = m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList.size();
				_ftprintf(fp, _T("%s %d %s %d\n"),
					L"SUBMATERIAL",
					iSubMtrl,
					L"TEXTURENUM",
					iNumTex);
			
				for (int iTex = 0; iTex < iNumTex; iTex++)
				{
					_ftprintf(fp, _T("%s %d %d %s\n"),
						L"TEXTURE",


						iTex,
						m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].iSubNo,
						m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].szTextureName);

				}

			}
		}
		else
		{
			int iNumTex = m_ExpMtlList[iMtrl].m_MapList.size();
			_ftprintf(fp, _T("%s %d %d\n"), L"TEXTURE", iMtrl,
				m_ExpMtlList[iMtrl].m_MapList.size());

			for (int iTex = 0; iTex < iNumTex; iTex++)
			{
				_ftprintf(fp, _T("%s %d %d %s\n"),
					L"TEXTURE",
					iTex,
					m_ExpMtlList[iMtrl].m_MapList[iTex].iSubNo,
					m_ExpMtlList[iMtrl].m_MapList[iTex].szTextureName);

			}
		}

	}

	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
	{
		
		_ftprintf(fp, _T("%s %d %s %d %s %d\n"),
			L"OBJECT",
			iObj, L"VERTEXNUM", m_ExpObject[iObj].m_TriList.size(),_T("REF"),m_ExpObject[iObj].m_iRef);
		
		_ftprintf(fp, _T("\t%s\n"), _T("WORLD_MATRIX"));
		_ftprintf(fp, _T("\t%10.4f %10.4f %10.4f %10.4f\n"),
			m_ExpObject[iObj].m_matWorld._11, m_ExpObject[iObj].m_matWorld._12, m_ExpObject[iObj].m_matWorld._13, m_ExpObject[iObj].m_matWorld._14);
		_ftprintf(fp, _T("\t%10.4f %10.4f %10.4f %10.4f\n"),
			m_ExpObject[iObj].m_matWorld._21, m_ExpObject[iObj].m_matWorld._22, m_ExpObject[iObj].m_matWorld._23, m_ExpObject[iObj].m_matWorld._24);
		_ftprintf(fp, _T("\t%10.4f %10.4f %10.4f %10.4f\n"),
			m_ExpObject[iObj].m_matWorld._31, m_ExpObject[iObj].m_matWorld._32, m_ExpObject[iObj].m_matWorld._33, m_ExpObject[iObj].m_matWorld._34);
		_ftprintf(fp, _T("\t%10.4f %10.4f %10.4f %10.4f\n"),
			m_ExpObject[iObj].m_matWorld._41, m_ExpObject[iObj].m_matWorld._42, m_ExpObject[iObj].m_matWorld._43, m_ExpObject[iObj].m_matWorld._44);

		std::sort(m_ExpObject[iObj].m_TriList.begin(), m_ExpObject[iObj].m_TriList.end(), DescendingDateSort());
		int iNumFace = m_ExpObject[iObj].m_TriList.size();
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			int iSubIndex = m_ExpObject[iObj].m_TriList[iFace].iSubIndex;
			int LastSubIndex = -1;
			if (iSubIndex!=LastSubIndex&&iSubIndex!=-1)
			{
				_ftprintf(fp, _T("%s %d\n"),L"MTLID",m_ExpObject[iObj].m_TriList[iFace].iSubIndex);
			}
			int iNumVertex = 3;
			for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
			{


				_ftprintf(fp, _T("\t%10.4f %10.4f %10.4f\n \t%10.4f %10.4f %10.4f\n \t%10.4f %10.4f %10.4f %10.4f\n \t%10.4f %10.4f \n"),
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.x,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.y,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.z,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.x,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.y,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.z,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.x,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.y,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.z,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.w,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].t.x,
					m_ExpObject[iObj].m_TriList[iFace].v[iVertex].t.y);
			}
			LastSubIndex = iSubIndex;
		}
		_ftprintf(fp, _T("%s \n"), L"ANIMATION");
		_ftprintf(fp, _T("%s \n"), L"POSTRACK");
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackPos.size(); iTrack++)
		{
			_ftprintf(fp, _T("\t %d %10.4f %10.4f %10.4f \n"),
			
				m_ExpObject[iObj].m_AnimTrackPos[iTrack].iTick,
				m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.x,
				m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.y,
				m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.z );

		}
		_ftprintf(fp, _T("%s \n"), L"ROTATETRACK");
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackRotate.size(); iTrack++)
		{
			_ftprintf(fp, _T("\t %d %10.4f %10.4f %10.4f %10.4f \n"),
				
				m_ExpObject[iObj].m_AnimTrackRotate[iTrack].iTick,
				m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.x,
				m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.y,
				m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.z);

		}
		_ftprintf(fp, _T("%s \n"), L"SCALETRACK");
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackScale.size(); iTrack++)
		{
			_ftprintf(fp, _T("\t %d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f \n"),
				
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].iTick,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.x,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.y,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.z,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.x,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.y,
				m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.z);

		}
	}

	fclose(fp);

	return true;
}
bool GlobalExp::EqualPoint1(float p1, float p2)
{
	if (fabs(p1 - p2) > ALMOST_ZERO)
		return false;
	return true;
}
bool GlobalExp::EqualPoint2(Point2 p1, Point2 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	return true;
}
bool GlobalExp::EqualPoint3(Point3 p1, Point3 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;

	return true;
}
bool GlobalExp::EqualPoint4(Point4 p1, Point4 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;
	if (fabs(p1.w - p2.w) > ALMOST_ZERO)
		return false;
	return true;
}
GlobalExp::GlobalExp()
{
}


GlobalExp::~GlobalExp()
{
}
