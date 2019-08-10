#include "CollisionCircle.h"



CollisionCircle::CollisionCircle()
{
}


CollisionCircle::CollisionCircle(sf::FloatRect Bounds, int range)
{
	this->CollisionBox.setRadius(range * 10);
	this->CollisionBox.setOrigin(this->CollisionBox.getRadius(), this->CollisionBox.getRadius());
	this->CollisionBox.setPosition(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
	this->CollisionBox.setFillColor(sf::Color(0,0,0,20));
}

CollisionCircle::~CollisionCircle()
{
}

void CollisionCircle::render(sf::RenderTarget * target)
{
	target->draw(this->CollisionBox);
}


//bool CollisionCircle::intersects(const sf::FloatRect &bounds)
//{
//	return (this->CollisionBox.getGlobalBounds().intersects(bounds));
//}

const sf::FloatRect CollisionCircle::GetBoundary()
{
	return this->CollisionBox.getGlobalBounds();
}

const float CollisionCircle::GetRadius()
{
	return this->CollisionBox.getRadius();
}
