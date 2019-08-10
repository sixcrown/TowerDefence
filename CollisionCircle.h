#pragma once
#include "includes.h"
#include "Enemy.h"
class CollisionCircle
{
private:
	sf::CircleShape CollisionBox;
	sf::Sprite CollisionSprite;
public:
	CollisionCircle();
	CollisionCircle(sf::FloatRect Bounds,int range);
	~CollisionCircle();
	void render(sf::RenderTarget *target);
	//bool intersects(const sf::FloatRect &bounds);
	const sf::FloatRect GetBoundary();
	const float GetRadius();
};

