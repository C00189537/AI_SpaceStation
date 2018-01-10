#pragma once
#include "Bullet.h"
class HomingMissiles :
	public Bullet
{
public:
	HomingMissiles();
	~HomingMissiles();
	void update();
};

