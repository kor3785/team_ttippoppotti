#pragma once
#include "singletonBase.h"
class frameManager : public singletonBase<frameManager>
{
	
public:
	void frameChange(image* img, int& count, int& index, int &speed, bool isLeft);
	
	//�����ӸŴ��� �ʱ�ȭ
	HRESULT init();
	//�����ӸŴ��� ����
	void release();

	frameManager() {}
	~frameManager() {}
};