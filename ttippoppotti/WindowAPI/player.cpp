#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	//����(�÷��̾�) �̹��� �ʱ�ȭ �� ��ġ ����
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));

	//�̻��� Ŭ���� ���� �� �ʱ�ȭ
	_missile = new missile;
	_missile->init(5, 500);

	//�̻���M1 Ŭ���� ���� �� �ʱ�ȭ
	_missileM1 = new missileM1;
	_missileM1->init(3, 600);

	return S_OK;
}

void player::release(void)
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
	//�̻���M1 Ŭ���� ����
	_missileM1->release();
	SAFE_DELETE(_missileM1);
}

void player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() + _rocket->getWidth() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);

	}

	//�Ѿ˹߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//�Ѿ�Ŭ������ �ϲ� �߻����
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//��ź�߻�
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//�̻���M1 Ŭ������ �ϲ� �߻����
		_missileM1->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//�̻��� Ŭ���� ������Ʈ
	_missile->update();
	//�̻���M1 Ŭ���� ������Ʈ
	_missileM1->update();

	//�浹�Լ�
	this->collision();
}

void player::render(void)
{
	//�����̹��� ����
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());

	//�̻��� Ŭ���� ����
	_missile->render();
	//�̻���M1 Ŭ���� ����
	_missileM1->render();
}

void player::removeMissileM1(int index)
{
	//�̻���M1 �ϰ� �Ѿ� ������!!!
	_missileM1->removeMissileM1(index);
}

//�浹�Լ�(�÷��̾��� �Ѿ˵� ���Ŵ����� �̴Ͼ�)
void player::collision()
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_missileM1->removeMissileM1(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}
