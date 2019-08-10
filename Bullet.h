#pragma once
#include "includes.h"
#include "Enemy.h"
class Bullet
{
private:
	sf::Vector2f moveVector;
	sf::Sprite pellet;
	std::shared_ptr<Enemy> target;
	int damage;
	float movementspeed;
	bool DeleteIndicator;
public:
	Bullet(sf::FloatRect starting_point, std::shared_ptr<Enemy> targeted_Enemy,sf::Texture *bullet_texture, int towerdamage, float BulletMovementSpeed);
	void CalculateVectorOfMove();
	void update(const float &dt);
	void render(sf::RenderTarget *target);
	void CheckForCollisionWithItsTarget();
	const bool GetDelete();
	int getDamage();
	float calculate_rotation();
	~Bullet();
};

