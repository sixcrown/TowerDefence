#include "Collision_Manager.h"
#include "Collision.h"



void Collision_Manager::initBulletTextures()
{
	std::string a = "couldnt load bullet textures";
	try 
	{
		if
		(!this->FireBulletTexture.loadFromFile("Resources/Images/Tiles/Fireball.png")||
		!this->ArrowBulletTexture.loadFromFile("Resources/Images/Tiles/Arrow.png")||
		!this->LightBulletTexture.loadFromFile("Resources/Images/Tiles/Lightball.png")||
		!this->LightningBulletTexture.loadFromFile("Resources/Images/Tiles/LightningBall.png"))
		{
			throw(a);
		}
	}
	catch (const std::string &a)
	{
		std::cout << a;
			system("exit");
	}
}

void Collision_Manager::CheckTowerEnemyCollision()
{
	if (this->CheckTimeForCollisionDetection()) {
		for (auto it = this->Towers->begin(); it != this->Towers->end(); ++it)
		{
			if (auto tmp = std::dynamic_pointer_cast<FireTower>(*it))
			{
				this->FireTowerCollision(tmp);
			}
			if (auto tmp = std::dynamic_pointer_cast<LightningTower>(*it))
			{
				if (tmp->CheckIfItsTimeToShoot()) 
				{
					this->LightningTowerCollision(tmp);
				}
			}
			if (auto tmp = std::dynamic_pointer_cast<LightTower>(*it))
			{
					this->LightTowerCollision(tmp);
			}
			if (auto tmp = std::dynamic_pointer_cast<ArrowTower>(*it))
			{
				this->ArrowTowerCollision(tmp);
			
			}
		}
	}
}
void Collision_Manager::CheckForBulletsToDelete()
{
	for (auto it =this->bullets->begin(); it!= this->bullets->end();++it)
	{
		(*it)->CheckForCollisionWithItsTarget();
	}
}
void Collision_Manager::shuffleVectorOfEnemies()
{
	std::random_shuffle(this->Enemies->begin(), this->Enemies->end());
}
void Collision_Manager::FireTowerCollision(std::shared_ptr<FireTower> Tower)
{
	this->shuffleVectorOfEnemies();
	for (auto it1 = this->Enemies->begin(); it1 != this->Enemies->end(); ++it1)
	{
		if (this->CheckEdges(Tower->GetCircle().GetBoundary(), Tower->GetCircle().GetRadius(), (*it1)->GetGlobalBounds()))
		{
			if ((Tower)->CheckIfItsTimeToShoot())
			{
				this->bullets->emplace_back(std::make_shared<Bullet>((Tower)->getGlobalBounds(), (*it1), &this->FireBulletTexture, (Tower)->getTowerDamage(), (Tower)->getBulletMovementSpeed()));
				std::cout << "Collision" << std::endl;
				break;
			}
		}
	}
}
void Collision_Manager::LightTowerCollision(std::shared_ptr<LightTower> Tower)
{
	for (auto it1 = this->Enemies->begin(); it1 != this->Enemies->end(); ++it1)
	{
		if (this->CheckEdges(Tower->GetCircle().GetBoundary(), Tower->GetCircle().GetRadius(), (*it1)->GetGlobalBounds()))
		{
			if ((Tower)->CheckIfItsTimeToShoot())
			{
				this->bullets->emplace_back(std::make_shared<Bullet>((Tower)->getGlobalBounds(), (*it1), &this->LightBulletTexture, (Tower)->getTowerDamage(), (Tower)->getBulletMovementSpeed()));
				std::cout << "Collision" << std::endl;
			}
		}
	}
}
void Collision_Manager::LightningTowerCollision(std::shared_ptr<LightningTower> Tower)
{
	for (auto it1 = this->Enemies->begin(); it1 != this->Enemies->end(); ++it1)
	{
		if (this->CheckEdges(Tower->GetCircle().GetBoundary(), Tower->GetCircle().GetRadius(), (*it1)->GetGlobalBounds()))
		{
			this->bullets->emplace_back(std::make_shared<Bullet>((Tower)->getGlobalBounds(), (*it1), &this->LightningBulletTexture, (Tower)->getTowerDamage(), (Tower)->getBulletMovementSpeed()));
			std::cout << "Collision" << std::endl;
		}
	}
}
void Collision_Manager::ArrowTowerCollision(std::shared_ptr<ArrowTower> Tower)
{
	for (auto it1 = this->Enemies->begin(); it1 != this->Enemies->end(); ++it1)
	{
		if (this->CheckEdges(Tower->GetCircle().GetBoundary(), Tower->GetCircle().GetRadius(), (*it1)->GetGlobalBounds()))
		{
			if ((Tower)->CheckIfItsTimeToShoot())
			{
				this->bullets->emplace_back(std::make_shared<Bullet>((Tower)->getGlobalBounds(), (*it1), &this->ArrowBulletTexture, (Tower)->getTowerDamage(), (Tower)->getBulletMovementSpeed()));
				std::cout << "Collision" << std::endl;
			}
		}
	}
}
const bool Collision_Manager::CheckEdges(const sf::FloatRect Circle, const int CircleRadius, const sf::FloatRect Entity) {
	float circle_x = Circle.left + Circle.width/2;
	float circle_y = Circle.top + Circle.height/2;
	float distX = std::abs(circle_x - Entity.left - Entity.width / 2);
	float distY = std::abs(circle_y - Entity.top - Entity.height / 2);

	if (distX > (Entity.width / 2 + CircleRadius)) { return false; }
	if (distY > (Entity.height / 2 + CircleRadius)) { return false; }

	if (distX <= (Entity.width / 2)) { return true; }
	if (distY <= (Entity.height / 2)) { return true; }

	float dx = distX - Entity.width / 2;
	float dy = distY - Entity.height / 2;
	return (dx*dx + dy * dy <= (CircleRadius*CircleRadius));
}
void Collision_Manager::initCollisionClock()
{
	this->CollisionClock = new sf::Clock;
	this->CollisionClock->restart();
}
const bool Collision_Manager::CheckTimeForCollisionDetection()
{
	if (this->cooldown <= this->CollisionClock->getElapsedTime().asSeconds())
	{
		this->CollisionClock->restart();
		return true;
	}
	return false;
}

void Collision_Manager::DeleteIntersectingBullets()
{
	bool done = false;
	int counter = 0;
	for (auto it = this->bullets->begin(); it != this->bullets->end(); ++it)
	{
		if ((*it)->GetDelete()) 
		{

			(*it).reset();
			/*if (it + 1 == this->bullets->end())
			{
				this->bullets->erase(std::remove(this->bullets->begin(), this->bullets->end(), (*it)), this->bullets->end());
				counter++;
				break;
			}
			else
			{
				this->bullets->erase(std::remove(this->bullets->begin(), this->bullets->end(), (*it)), this->bullets->end());
				counter++;
			}*/
		}
	}

	//this->bullets->erase(std::remove_if(this->bullets->begin(), this->bullets->end(), it==nullptr, this->bullets->end());
	this->bullets->erase(std::remove(this->bullets->begin(), this->bullets->end(), nullptr), this->bullets->end());
	
	
}

int Collision_Manager::checkForEnemyDeletion()
{
	int sum = 0;
	for (auto it = this->Enemies->begin(); it != this->Enemies->end(); it++)
	{
		if ((*it)->getto_delete())
		{
			sum += (*it)->GetGold();			
			(*it).reset();
		
			/*if (it + 1 == this->Enemies->end())
			{
				sum += (*it)->GetGold();
				this->Enemies->erase(std::remove(this->Enemies->begin(), this->Enemies->end(), (*it)), this->Enemies->end());
				break;
			}
			else
			{
				sum += (*it)->GetGold();
				this->Enemies->erase(std::remove(this->Enemies->begin(), this->Enemies->end(), (*it)), this->Enemies->end());
			}*/

		}
	}
	this->Enemies->erase(std::remove(this->Enemies->begin(), this->Enemies->end(), nullptr), this->Enemies->end());
	return sum;
}

int Collision_Manager::CheckForNexusIntersection()
{
	int sum = 0;
	for (auto it = this->Enemies->begin(); it != this->Enemies->end(); ++it)
	{
		if ((*it)->intersectionWithNexus())
		{
			sum++;
			(*it).reset();
		}
	}
	this->Enemies->erase(std::remove(this->Enemies->begin(), this->Enemies->end(), nullptr), this->Enemies->end());
	return sum;
}

Collision_Manager::Collision_Manager()
{
	this->cooldown = 0.1f;
	this->initCollisionClock();
	this->initBulletTextures();
}


Collision_Manager::~Collision_Manager()
{
	delete this->CollisionClock;
}
