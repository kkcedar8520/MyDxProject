#pragma once
#include "GustStage.h"

class StageSene;
class Stage;

void GustStage::Process(JHObject*Obj)
{
	if (m_iCheck==0)
	{
		m_pOwner->Load(L"bitmap/GUTSMAP.bmp");
		m_iCheck++;
	}

}

GustStage::~GustStage()
{
}
