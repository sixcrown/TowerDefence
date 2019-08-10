#include "Enemy.h"



int Enemy::getHp()
{
	return this->hp;
}

void Enemy::setHp(int damage)
{
	this->hp -= damage;
	this->CheckForDeletion();
}

void Enemy::CheckForDeletion()
{
	if (this->hp <= 0)
	{
		this->to_delete = true;
	}
}

bool Enemy::getto_delete()
{
	return this->to_delete;
}

void Enemy::getMovementFromFile()
{
	std::fstream file;
	file.open("Config/Enemy.ini");
	int it;
	file >> it;
	for (int i = 0; i < it; i++)
	{
		auto tmp = new Move();
		file >> tmp->move_rect.left;
		file >> tmp->move_rect.top;
		file >> tmp->move_rect.width;
		file >> tmp->move_rect.height;
		file >> tmp->direction;
		this->movement.push_front(tmp);
	}
	this->movement.reverse();
}

void Enemy::GetTextureFromFile()
{
	this->texture.loadFromFile("Resources/Images/Tiles/BadGuy.png");
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->Enemy_sprite);
	target->draw(this->Enemy_Hp);
}

void Enemy::move(const float &dt)
{
	count++;
	switch (this->spriteDirection)
	{
	case DOWN:
	{
		this->current_pos = this->Enemy_sprite.getPosition();
		this->moveDown(dt);
		this->current_pos = this->Enemy_sprite.getPosition();
	}
	break;
	case RIGHT:
	{
		this->current_pos = this->Enemy_sprite.getPosition();
		this->moveRight(dt);
		this->current_pos = this->Enemy_sprite.getPosition();
	}
	}
}

void Enemy::update(const float &dt)
{
	if (this->count%2==0)
	{
		this->count = 0;
		this->rect.left += this->rect.width;
		this->Enemy_sprite.setTextureRect(this->rect);
	}
	else
	{
		this->rect.left -= this->rect.width;
		this->Enemy_sprite.setTextureRect(this->rect);
	}
	this->move(dt);
	this->Enemy_Hp.setString(std::to_string(this->hp));
	this->Enemy_Hp.setPosition(this->Enemy_sprite.getGlobalBounds().left, this->Enemy_sprite.getGlobalBounds().top-this->Enemy_sprite.getGlobalBounds().height/2);
}

void Enemy::moveDown(const float & dt)
{
	this->CheckIfItsTimeToChange();
	this->CheckMoveDownEnd(); 
	
		switch (this->dir)
		{
		case Dir1:
		{
			if ((this->starting_pos.x + this->movement.front()->move_rect.width > this->current_pos.x + 1)
				&& this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveDown();
			}
		}
		break;
		case Dir2:
		{
			if ((this->starting_pos.x < this->current_pos.x - 1)
				&& this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveDown();
			}
		}
		break;
		case Dir3:
		{
			if (this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveDown();
			}
		}
		break;
		case Dir4:
		{
			if (this->starting_pos.x + this->movement.front()->move_rect.width > this->current_pos.x + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveDown();
			}
		}
		break;
		case Dir5:
		{
			if (this->starting_pos.x < this->current_pos.x - 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveDown();
			}
		}
		break;
		case DirEnd:
			break;
		}
	
}

bool Enemy::CheckMoveDownEnd()
{
	if (this->current_pos.y> this->starting_pos.y+this->movement.front()->move_rect.height -2)
	{
		auto g = this->current_pos.y;
		auto f = this->starting_pos.y + this->movement.front()->move_rect.height - 1;
		this->movement.pop_front();
		this->dir = DirEnd;
		if (!this->movement.empty())
		{
			this->spriteDirection = this->movement.front()->direction;
			this->starting_pos = sf::Vector2f(this->movement.front()->move_rect.left, this->movement.front()->move_rect.top);
		}
		return true;
	}
	return false;
}

void Enemy::SetVectorOfMoveDown()
{
	int count = 0;
	bool left = false; // sterable variables
	bool right = false;
	bool leftCorner = false;
	bool rightCorner = false;
	bool forward = false;
	bool movement_done = false;

	while (!movement_done)
	{
		
		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> dis(1, 8);
		auto p = dis(gen);
		if ((p == 1||p==6)&&(!right&&!rightCorner))
		{
			
			if ((this->starting_pos.x + this->movement.front()->move_rect.width > this->current_pos.x + 1))
			{
				this->VectorOfMove =(sf::Vector2f(1.f, 1.f));
				this->dir = Dir1;
				movement_done = true;
			}
			else {
				rightCorner = true;
				count++;
			}
			
		}
		else if ((p == 2||p==7)&& (!left && !leftCorner))
		{
			if ((this->starting_pos.x < this->current_pos.x - 1))
			{
				this->VectorOfMove = (sf::Vector2f(-1.f, 1.f));
				this->dir = Dir2;
				movement_done = true;
			}
			else { 
				leftCorner = true;
				count++;
			}
		}
		else if ((p == 3) &&!left)
		{
			if (this->starting_pos.x < this->current_pos.x - 1)
			{
				this->dir = Dir5;
				this->VectorOfMove = sf::Vector2f(-1.f, 0.f);
				movement_done = true;
			}
			else { 
				left = true;
				count++;
			}
		}
		else if (p == 4 && !right)
		{
			if (this->starting_pos.x + this->movement.front()->move_rect.width > this->current_pos.x + 1)
			{
				this->dir = Dir4;
				this->VectorOfMove = sf::Vector2f(1.f, 0.f);
				movement_done = true;
			}
			else
			{ 
				count++;
				right = true;
			}
		}
		if ((p == 5 || p == 8) || count >= 2)
		{
			if (this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->VectorOfMove = (sf::Vector2f(0.f, 1.f));
				this->dir = Dir3;
				movement_done = true;
			}
			else
			{
				forward = false;
			}

		}
	}
}


void Enemy::CheckIfItsTimeToChange()
{
	if (this->EnemyClock->getElapsedTime().asSeconds() > this->CoolDown)
	{
		this->EnemyClock->restart();
		if (this->spriteDirection == DOWN)
		{
			this->SetVectorOfMoveDown();
		}
		else if(this->spriteDirection == RIGHT)
		{
			this->SetVectorOfMoveRight();
		}
		
	}
}

const sf::Sprite & Enemy::GetSprite()
{
	return this->Enemy_sprite;
}

void Enemy::operator-(const int damage)
{
	this->hp -= damage;
}

int Enemy::GetGold()
{
	return this->goldgiven;
}

sf::FloatRect Enemy::GetGlobalBounds()
{
	return this->Enemy_sprite.getGlobalBounds();
}

const bool Enemy::intersectionWithNexus()
{
	if (this->Enemy_sprite.getGlobalBounds().intersects(this->NexusRect)) return true;
	return false;
}

Enemy::Enemy(sf::Font &Font, int hp, sf::FloatRect NexusPosition)
{
	this->NexusRect = NexusPosition;
	this->count = 0;
	this->font = font;
	this->Enemy_Hp.setFont(Font);
	this->Enemy_Hp.setCharacterSize(13);
	this->Enemy_Hp.setFillColor(sf::Color(0,0,0));
	this->to_delete = false;
	this->hp = hp;
	this->goldgiven = 10;
	this->EnemyClock = new sf::Clock;
	this->CoolDown = 0.30f;
	this->rect.left = 0;
	this->rect.top = 0;
	this->rect.width = 23;
	this->rect.height = 38;
	this->spriteDirection = DOWN;
	this->Movementspeed = 50.f;
	this->getMovementFromFile();
	this->GetTextureFromFile();
	this->Enemy_sprite.setTexture(texture);
	this->starting_pos = sf::Vector2f(this->movement.front()->move_rect.left, this->movement.front()->move_rect.top);
	this->current_pos = sf::Vector2f(this->starting_pos.x+this->movement.front()->move_rect.width/2,this->starting_pos.y);
	this->Enemy_sprite.setPosition(this->current_pos);
	this->Enemy_Hp.setString(std::to_string(this->hp));
	this->Enemy_Hp.setPosition(this->Enemy_sprite.getGlobalBounds().left, this->Enemy_sprite.getGlobalBounds().top);

}
void Enemy::moveRight(const float & dt)
{
	this->CheckIfItsTimeToChange();
	this->CheckMoveRightEnd();
	
		switch (this->dir)
		{
		case Dir5:
		{
			if ((this->starting_pos.y - 1 < this->current_pos.y))
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveRight();
			}
		}
		break;
		case Dir1:
		{
			if ((this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y - 1))
			{
				auto a = this->starting_pos.y + this->movement.front()->move_rect.height < this->current_pos.x - 1;
				auto b = this->current_pos.x + 1 < this->starting_pos.x + this->movement.front()->move_rect.width;
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveRight();
			}
		}
		break;
		case Dir4:
		{
			if ( this->current_pos.x < this->starting_pos.x + this->movement.front()->move_rect.width - 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveRight();
			}
		}
		break;
		case Dir3:
			if (this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveRight();
			}
		break;
		case Dir2:
			if (this->starting_pos.x < this->current_pos.x + 1)
			{
				this->Enemy_sprite.move(this->VectorOfMove*dt*this->Movementspeed);
				this->current_pos = this->Enemy_sprite.getPosition();
			}
			else
			{
				this->SetVectorOfMoveRight();
			}
		break;
		case DirEnd:
			break;
		}
	
}

void Enemy::SetVectorOfMoveRight()
{
	int it = 0;
	bool movement_done = false;

	while (!movement_done)
	{

		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> dis(1,8);
		auto p = dis(gen);
		if ((p == 1 ||p==6) )//upright
		{
			if ((this->starting_pos.y - 1 <this->current_pos.y))
			{
				this->VectorOfMove = (sf::Vector2f(1.f, -1.f));
				this->dir = Dir5;
				movement_done = true;
			}
			else
			{
				it++;
			}
		}
		else if ((p == 2||p==7)) //downright
		{
			if ((this->starting_pos.y+this->movement.front()->move_rect.height - 1 > this->current_pos.y ))
			{
				this->VectorOfMove = (sf::Vector2f(1.f, 1.f));
				this->dir = Dir1;
				movement_done = true;
			}
			else
			{
				it++;
			}
		}
		else if (p == 3 )//down
		{
			if (this->starting_pos.y + this->movement.front()->move_rect.height > this->current_pos.y + 1)
			{
				this->dir = Dir3;
				this->VectorOfMove = sf::Vector2f(0.f, 1.f);
				movement_done = true;
			}
			else
			{
				it++;
			}
		}
		else if(p==4)//up
		{
			if (this->current_pos.y -1>this->starting_pos.y)
			{
				this->VectorOfMove = (sf::Vector2f(0.f, -1.f));
				this->dir = Dir2;
				movement_done = true;
			}
		}
		if((p==5||p==8)||it>=2)//right
		{
			if (this->starting_pos.x < this->current_pos.x + 1)
			{
				this->dir = Dir4;
				this->VectorOfMove = sf::Vector2f(1.f, 0.f);
				movement_done = true;
			}
			else {
				it++;
			}
		}
	}
}

bool Enemy::CheckMoveRightEnd()
{
	if (this->current_pos.x > this->starting_pos.x + this->movement.front()->move_rect.width)
	{
		auto p = this->current_pos.x + 1;
		auto a = this->starting_pos.x + this->movement.front()->move_rect.width;
		this->movement.pop_front();
		//this->movement.reverse();
		this->dir = DirEnd;
		if (!this->movement.empty())
		{
			
			this->spriteDirection = this->movement.front()->direction;
			this->starting_pos = sf::Vector2f(this->movement.front()->move_rect.left, this->movement.front()->move_rect.top);
		}
		return true;
	}
	return false;
}


Enemy::~Enemy()
{
	while (!this->movement.empty())
	{
		this->movement.pop_front();
	}
	delete this->EnemyClock;
}
