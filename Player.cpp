#include "Player.h"



Player::Player()
{
	this->InitPlayerFromFile();
}

void Player::getGoldFromTimePassed(sf::Clock *Gameclock)
{
	if (Gameclock->getElapsedTime().asSeconds() > this->TimeInterwalsToGetGold)
	{
		Gameclock->restart();
		this->gold += 1;
	}
}

void Player::getGoldFromMonster(int MonsterValue)
{
	this->gold += MonsterValue;
}

void Player::LoseGoldFromBuying(int TurretValue)
{
	this->gold -= TurretValue;
}

void Player::LoseHp(int hp_to_lose)
{
	this->hp -= hp_to_lose;
}


Player::~Player()
{
}

int Player::GetCurrentGold()
{
	return this->gold;
}

int Player::GetCurrentHp()
{
	return this->hp;
}

void Player::InitPlayerFromFile()
{
	std::fstream file;
	file.exceptions(std::fstream::failbit | std::fstream::badbit);
	try 
	{
		file.open("Config/player.ini");
	}
	catch (const std::fstream::failure& e)
	{
		std::cout << e.what();
	}
		
	file >> this->TimeInterwalsToGetGold;
	file >> this->hp;
	file >> this->gold;
	file.close();
}
