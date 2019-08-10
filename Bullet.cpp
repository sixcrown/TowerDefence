#include "Bullet.h"






Bullet::Bullet(sf::FloatRect starting_point, std::shared_ptr<Enemy> targeted_Enemy, sf::Texture * bullet_texture, int towerdamage, float BulletMovementSpeed)
	:target(targeted_Enemy)
{
	this->DeleteIndicator = false;
	//this->initTexFromFile();
	this->damage = towerdamage;
	this->movementspeed = BulletMovementSpeed;
	this->pellet.setTexture(*bullet_texture);
	this->pellet.setPosition(starting_point.left + starting_point.width / 2, starting_point.top + starting_point.height / 2);
	this->pellet.move(-this->pellet.getGlobalBounds().width / 2, -this->pellet.getGlobalBounds().height / 2);
}


void Bullet::CalculateVectorOfMove()
{
	auto px = this->target->GetGlobalBounds().left + this->target->GetGlobalBounds().width / 2; //center of the enemy
	auto py = this->target->GetGlobalBounds().top + this->target->GetGlobalBounds().height / 2;
	auto x =px - (this->pellet.getGlobalBounds().left + this->pellet.getGlobalBounds().width);
	auto y = py - (this->pellet.getGlobalBounds().top + this->pellet.getGlobalBounds().height);
	auto lenght = sqrt(pow(x, 2) + pow(y, 2));
	this->moveVector = sf::Vector2f(x / lenght, y / lenght);
}

void Bullet::update(const float & dt)
{
	if (this->target) 
	{
		this->CalculateVectorOfMove();
		this->calculate_rotation();
		//this->pellet.setRotation(this->calculate_rotation());
		this->pellet.move(this->moveVector*this->movementspeed*dt);
	}
	else this->DeleteIndicator = true;
}

void Bullet::render(sf::RenderTarget * target)
{
	target->draw(this->pellet);
}

void Bullet::CheckForCollisionWithItsTarget()
{
	if (this->target->GetGlobalBounds().intersects(this->pellet.getGlobalBounds())&&!this->DeleteIndicator)
	{
		this->target->setHp(this->damage);
		this->DeleteIndicator = true;
	}
}

const bool Bullet::GetDelete()
{
	if (this->DeleteIndicator == true)
	{
		return true;
	}
	else return false;
}

int Bullet::getDamage()
{
	return this->damage;
}

float Bullet::calculate_rotation()
{
	auto a = (atan2(this->moveVector.y, this->moveVector.x)*180.f)/3.14f;
	this->pellet.setRotation(a);
	return 0;
}

Bullet::~Bullet()
{
	this->target.reset();
}
