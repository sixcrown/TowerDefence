#include "TIle.h"
Tiles::Tiles()
{
	this->type = "";
}

Tiles::Tiles(int x, int y, const sf::Texture *texture, std::string type)
{

	if (type == "Base") 
	{ 
		this->shape.setScale(sf::Vector2f(1, 1));
		this->shape.setPosition(x-20, y-70);
	}
	else 
	{ 
		this->shape.setScale(sf::Vector2f(0.5, 0.5));
		this->shape.setPosition(x, y);
	}
	this->shape.setTexture(*texture);

	this->type = type;
}

Tiles::~Tiles()
{

}

//Accessors
const std::string & Tiles::getType() const
{
	return this->type;
}

const sf::Sprite & Tiles::getShape() const
{
	return this->shape;
}


const sf::Vector2f & Tiles::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tiles::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions


void Tiles::update()
{

}

void Tiles::render(sf::RenderTarget * target,  const sf::Vector2f player_position)
{
	
		target->draw(this->shape);

}

Tower::Tower()
{
}

Tower::Tower(sf::Sprite a)
{
	this->range = 0;
	this->damage = 0;
	this->shape = a;
	this->type = "empty";
}

const bool & Tower::isClicked(const sf::Vector2f & MousePos) const
{
	if (this->getGlobalBounds().contains(MousePos)&&sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{	
		return true;
	}
	return false;
}

void Tower::initTowerDisplayInfo()
{
	std::fstream file;
	file.open("Config/TowerInfo.ini");
	file >> this->bounds.top;
	file >> this->bounds.left;
	file >> this->bounds.width;
	file >> this->bounds.height;
		
}

int Tower::getLevel()
{
	return this->level;
}

CollisionCircle Tower::GetCircle()
{
	return *this->circle;
}

//void Tower::GetCollisionInfo(const sf::FloatRect bounds)
//{
//	if (this->circle->getGlobalBounds().intersects(bounds))
//	{
//		std::cout << "OJ TAK TU JEST KOLIZYJKA" << std::endl;
//	}
//	//else std::cout << "Kolizyjki ni ma";
//}

void FireTower::initTexture()
{
	this->texture.loadFromFile("Resources/Images/Tiles/FireTower.png");
}



FireTower::FireTower(sf::Sprite a)
{
	this->BulletMovementSpeed = 160.f;
	this->ShootCooldown = 0.5f;
	this->type = "Fire";
	this->damage = 5;
	this->range = 20;
	this->level = 1;
	this->shape = a;
	this->initTexture();
	this->initTowerDisplayInfo();
	this->Display.setTexture(texture);
	this->Display.setTextureRect(this->bounds);
	this->Display.setPosition(this->shape.getPosition().x + 3, this->shape.getPosition().y - 2* this->bounds.height/3);
	this->initShootClock();
	this->initCollisionCircle();
}

void FireTower::render(sf::RenderTarget * target, const sf::Vector2f player_position)
{
	target->draw(this->shape);
	target->draw(this->Display);
	this->circle->render(target);
}

void FireTower::update()
{
	if (static_cast<int>(this->level) != 3)
	{
		this->ShootCooldown -= 0.1f;
		this->BulletMovementSpeed += 20.f;
		this->damage += 5;
		this->range += 3;
		this->level += 1;
		this->bounds.left += 40;
		this->redrawCollisionCircle();
	}
	this->Display.setTextureRect(this->bounds);
}

FireTower::~FireTower()
{
	delete this->circle;
	delete this->ShootClock;
}

void Tower::initCollisionCircle()
{
	this->circle = new CollisionCircle(this->getGlobalBounds(), this->range);
}

void Tower::initShootClock()
{
	this->ShootClock = new sf::Clock;
	this->ShootClock->restart();
}

bool Tower::CheckIfItsTimeToShoot()
{
	if (this->ShootClock->getElapsedTime().asSeconds() >= this->ShootCooldown)
	{
		this->ShootClock->restart();
		return true;
	}
	return false;
}

void Tower::redrawCollisionCircle()
{
	delete this->circle;
	this->circle = new CollisionCircle(this->getGlobalBounds(), this->range);
}

const float Tower::getBulletMovementSpeed()
{
	return this->BulletMovementSpeed;
}

const int Tower::getTowerDamage()
{
	return this->damage;
}

void LightningTower::initTexture()
{
	this->texture.loadFromFile("Resources/Images/Tiles/LightningTurrets.png");
}

LightningTower::LightningTower(sf::Sprite a)
{
	this->BulletMovementSpeed = 100.f;
	this->ShootCooldown = 0.7f;
	this->type = "Lightning";
	this->damage = 1;
	this->range = 9;
	this->level = 1;
	this->shape = a;
	this->initTexture();
	this->initTowerDisplayInfo();
	this->Display.setTexture(texture);
	this->Display.setTextureRect(this->bounds);
	this->Display.setPosition(this->shape.getPosition().x + 3, this->shape.getPosition().y - 2 * this->bounds.height / 3);
	this->initCollisionCircle();
	this->initShootClock();
}

void LightningTower::render(sf::RenderTarget * target, const sf::Vector2f player_position)
{
	target->draw(this->shape);
	target->draw(this->Display);
	this->circle->render(target);
	
}

void LightningTower::update()
{
	if (static_cast<int>(this->level) != 3)
	{
		this->ShootCooldown -= 0.05f;
		this->BulletMovementSpeed += 20.f;
		this->damage += 1;
		this->range += 2;
		this->level += 1;
		this->bounds.left += 40;
		this->redrawCollisionCircle();
	}
	this->Display.setTextureRect(this->bounds);
}

LightningTower::~LightningTower()
{
	delete this->circle;
	delete this->ShootClock;
}

void ArrowTower::initTexture()
{
	this->texture.loadFromFile("Resources/Images/Tiles/ArrowTurrets.png");
}

ArrowTower::ArrowTower(sf::Sprite a)
{
	this->initShootClock();
	this->BulletMovementSpeed = 200.f;
	this->ShootCooldown = 0.5f;
	this->type = "Arrow";
	this->damage = 20;
	this->range = 20;
	this->level = 1;
	this->shape = a;
	this->initTexture();
	this->initTowerDisplayInfo();
	this->Display.setTexture(texture);
	this->Display.setTextureRect(this->bounds);
	this->Display.setPosition(this->shape.getPosition().x + 3, this->shape.getPosition().y - 2 * this->bounds.height / 3);
	this->initCollisionCircle();
}

void ArrowTower::render(sf::RenderTarget * target, const sf::Vector2f player_position)
{
	target->draw(this->shape);
	target->draw(this->Display);
	this->circle->render(target);
}

void ArrowTower::update()
{
	if (static_cast<int>(this->level) != 3)
	{
		this->ShootCooldown -= 0.1f;
		this->BulletMovementSpeed += 30.f;
		this->damage += 10;
		this->range += 10;
		this->level += 1;
		this->bounds.left += 40;
		this->redrawCollisionCircle();
	}
	this->Display.setTextureRect(this->bounds);
}

ArrowTower::~ArrowTower()
{
	delete this->circle;
	delete this->ShootClock;
}

void LightTower::initTexture()
{
	this->texture.loadFromFile("Resources/Images/Tiles/LightTurrets.png");
}

LightTower::LightTower(sf::Sprite a)
{
	this->ShootCooldown = 1.f;
	this->initShootClock();
	this->BulletMovementSpeed = 800.f;
	this->type = "Light";
	this->damage = 10;
	this->range = 30;
	this->level = 1;
	this->shape = a;
	this->initTexture();
	this->initTowerDisplayInfo();
	this->Display.setTexture(texture);
	this->Display.setTextureRect(this->bounds);
	this->Display.setPosition(this->shape.getPosition().x + 3, this->shape.getPosition().y - 2 * this->bounds.height / 3);
	this->initCollisionCircle();
}

void LightTower::render(sf::RenderTarget * target, const sf::Vector2f player_position)
{
	target->draw(this->shape);
	target->draw(this->Display);
	this->circle->render(target);
}

void LightTower::update()
{
	if (static_cast<int>(this->level) != 3)
	{
		this->ShootCooldown -= 0.25f;
		this->BulletMovementSpeed += 200.f;
		this->damage += 5;
		this->range += 4;
		this->level += 1;
		this->bounds.left += 40;
		this->redrawCollisionCircle();
	}
	this->Display.setTextureRect(this->bounds);
}

LightTower::~LightTower()
{
	delete this->circle;
	delete this->ShootClock;
}


