#include "Queue.h"


void Queue::Push(ServerObj* pObj)
{
		Lock PushLock(this);
		m_ObjList.push(pObj);

}
ServerObj* Queue::Pop()
{
	ServerObj* pObj;
	Lock PopLock(this);
	if (m_ObjList.size()!=0)
	{
		
		pObj=m_ObjList.front();
		m_ObjList.pop();
	}
	return pObj;
}
Queue::Queue()
{
}


Queue::~Queue()
{
}
