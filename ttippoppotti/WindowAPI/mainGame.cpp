#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�
	
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);

	//UFO ������ �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);

	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//�÷��̾� Ŭ���� ���� �� �ʱ�ȭ
	_player = new player;
	_player->init();

	//���ʹ̸Ŵ��� Ŭ���� ���� �� �ʱ�Ȯ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//�÷��̾�� ���Ŵ��� ��ȣ����
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	//�ȼ��浹 Ŭ���� ���� �� �ʱ�ȭ
	_pc = new pixelCollision;
	_pc->init();


	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
	//init�Լ����� �����Ҵ� new�� ����ߴٸ� �̰����� delete ����Ѵ�
	//�̹����Ŵ��� ���� safe_delete �� �ʿ� ����

	//�÷��̾� ����
	_player->release();
	SAFE_DELETE(_player);

	//���ʹ̸Ŵ��� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	//�ȼ��浹 ����
	_pc->release();
	SAFE_DELETE(_pc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�

	//�÷��̾� Ŭ���� ������Ʈ
	//_player->update();

	//���Ŵ��� Ŭ���� ������Ʈ
	//_enemyManager->update();
	//�浹�Լ�
	//this->collision();

	//�ȼ��浹 ������Ʈ
	_pc->update();

}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//��׶��� �̹��� ����
	//IMAGEMANAGER->render("��׶���", getMemDC());

	//�÷��̾� Ŭ���� ����
	//_player->render();

	//���ʹ̸Ŵ��� Ŭ���� ����
	//_enemyManager->render();

	//�ȼ��浹 ����
	_pc->render();

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}

void mainGame::collision()
{
	/*
	//�浹ó��
	//�÷��̾��� �Ѿ� & �� => �浹ó��
	//�÷��̾�� �Ѿ�Ŭ���� �����´�
	//�Ѿ�Ŭ�������� ���� �����´�
	//�÷��̾�->�̻���Ŭ����->�Ѿ˺���[]
	for (int i = 0; i < _player->getMissile()->getVBullet().size(); i++)
	{
		//RECT rc;//�ӽÿ뷺Ʈ
		//RECT rcEnemy;
		//RECT rcBullet = _player->getMissile()->getVBullet()[i].rc;
		//if (IntersectRect(&rc, &rcBullet, &rcEnemy))
		//{
		//
		//}
	}

	//���ʹ�Ŭ������ �Ѿ�Ŭ������ ������
	���ʹ̸Ŵ���->���ʹ�Ŭ����->�Ѿ�Ŭ����->�Ѿ˺���
	
	//���ʹ̸Ŵ������� �Ѿ�Ŭ���� ��� ������
	���ʹ̸Ŵ���->�Ѿ�Ŭ����->�Ѿ˺���

	*/

	//�÷��̾� �Ѿ� vs �̴Ͼ� �浹ó��
	for (int i = 0; i < _player->getMissile()->getVBullet().size(); i++)//�÷��̾ �� �Ѿ�
	{
		for (int j = 0; j < _enemyManager->getVMinion().size(); j++)//���ʹ�Ŭ����
		{
			//�浹�߳�?
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissile()->getVBullet()[i].rc,
				&_enemyManager->getVMinion()[j]->getRect()))
			{
				//�÷��̾� �Ѿ� ����
				_player->removeMissileM1(i);
				//�̴Ͼ� ����
				_enemyManager->removeMinion(j);
				break;
			}
		}
	}

}
