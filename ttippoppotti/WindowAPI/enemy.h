#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
class enemy : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	enemy() {}
	virtual ~enemy() {}
};

