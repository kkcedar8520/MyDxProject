// JH_MapPane.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "JH_MapPane.h"


// JH_MapPane

IMPLEMENT_DYNAMIC(JH_MapPane, CDockablePane)

JH_MapPane::JH_MapPane()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

JH_MapPane::~JH_MapPane()
{
}


BEGIN_MESSAGE_MAP(JH_MapPane, CDockablePane)
END_MESSAGE_MAP()



// JH_MapPane 메시지 처리기


