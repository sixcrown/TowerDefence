#pragma once
#include "TIle.h"
#include "includes.h"
#include "Bullet.h"

class Collision_Manager
{
private:
	sf::Clock *CollisionClock;
	float cooldown;
	sf::Texture FireBulletTexture;
	sf::Texture ArrowBulletTexture;
	sf::Texture LightBulletTexture;
	sf::Texture LightningBulletTexture;

public:
	void initBulletTextures();
	std::vector<std::shared_ptr<Tower>> *Towers;
	std::vector<std::shared_ptr<Enemy>> *Enemies;
	std::vector<std::shared_ptr<Bullet>> *bullets;
	void CheckTowerEnemyCollision();
	void CheckForBulletsToDelete();
	void shuffleVectorOfEnemies();
	void FireTowerCollision(std::shared_ptr<FireTower> Tower);
	void LightTowerCollision(std::shared_ptr<LightTower> Tower);
	void LightningTowerCollision(std::shared_ptr<LightningTower> Tower);
	void ArrowTowerCollision(std::shared_ptr<ArrowTower> Tower);
	const bool CheckEdges(const sf::FloatRect Circle, const int CircleRadius, const sf::FloatRect Entity);
	void initCollisionClock();
	const bool CheckTimeForCollisionDetection();
	void DeleteIntersectingBullets();
	int checkForEnemyDeletion();
	int CheckForNexusIntersection();
	Collision_Manager();
	~Collision_Manager();
};

