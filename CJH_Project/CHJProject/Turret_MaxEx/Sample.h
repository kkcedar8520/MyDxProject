#include"JHDXCore.h"
#include"MaxObj.h"
class Sample :public JHDXCore
{
public:
	MaxObj m_MaxBox;


public:

public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	Sample();
	virtual ~Sample();
};

