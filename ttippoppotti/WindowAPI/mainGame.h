#pragma once
#include "gameNode.h"
#include "player.h"	//�÷��̾� Ŭ���� ����ϱ� ����
#include "enemyManager.h"
#include "pixelCollision.h"

class mainGame : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

