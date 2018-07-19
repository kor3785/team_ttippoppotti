#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�
	
	_playerManager = new playerManager;
	_playerManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_backGround = IMAGEMANAGER->addImage("backGround", "background.bmp", 5296, 2131);

	_rcCamera = RectMake(0, 2131-1080, 5296, 2131-1080);
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

	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	_playerManager->update();
	_enemyManager->update();

	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_rcCamera.left > 0)
		{
			_rcCamera.left -= 5;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_rcCamera.right >= _rcCamera.left + 5 + 1920)
		{
			_rcCamera.left += 5;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_rcCamera.top > 5)
		{
			_rcCamera.top -= 5;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_rcCamera.bottom > _rcCamera.top + 5 + 1080)
		{
			_rcCamera.top += 5;
		}
	}
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	_backGround->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);

	_playerManager->render();
	_enemyManager->render();

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}
