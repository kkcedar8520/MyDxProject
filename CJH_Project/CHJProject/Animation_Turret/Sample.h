#include"JHDXCore.h"
#include"xAseObj.h"
class Sample :public JHDXCore
{
public:
	xAseObj m_AseBox;


public:

public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	Sample();
	virtual ~Sample();
};

