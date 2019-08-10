#pragma once
#include "includes.h"
class Player
{
private:
	double TimeInterwalsToGetGold;
	int gold;
	int hp;
public:
	Player();
	void getGoldFromTimePassed(sf::Clock *Gameclock);
	void getGoldFromMonster(int MonsterValue);
	void LoseGoldFromBuying(int TurretValue);
	void LoseHp(int hp_to_lose);
	int GetCurrentGold();
	int GetCurrentHp();
	void InitPlayerFromFile();
	~Player();
};

