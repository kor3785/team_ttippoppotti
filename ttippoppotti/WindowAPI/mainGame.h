#pragma once
#include "gameNode.h"
#include "player.h"	//플레이어 클래스 사용하기 위해
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

