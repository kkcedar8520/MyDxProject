#pragma once
#include "GustStage.h"

class StageSene;
class Stage;

void GustStage::Process(JHObject*Obj)
{
		m_pOwner->Load(L"bitmap/GUTSMAP.bmp");
}

GustStage::~GustStage()
{
}
