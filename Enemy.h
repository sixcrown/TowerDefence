#pragma once
#include "includes.h"
enum MOVEMENT{DOWN,RIGHT};
enum EnemyMove { Dir1, Dir2, Dir3, Dir4, Dir5, DirEnd };
class Move
{
public:
	sf::FloatRect move_rect;
	short direction;
};

class Enemy
{
private:
	sf::Font *font;
	sf::Text Enemy_Hp;
	sf::IntRect rect;
	sf::Sprite Enemy_sprite;
	sf::Texture texture;
	sf::FloatRect NexusRect;
	short spriteDirection;
	short dir;
	int goldgiven;
	int hp;
	int count;
	float Movementspeed;
	sf::Clock *EnemyClock;
	float CoolDown;
	sf::Vector2f VectorOfMove;
	bool to_delete;
	sf::Vector2f starting_pos;
	sf::Vector2f current_pos;

	std::forward_list<Move*> movement;
public:
	int getHp();
	void setHp(int damage);
	void CheckForDeletion();
	bool getto_delete();
	void getMovementFromFile();
	void GetTextureFromFile();
	void render(sf::RenderTarget *target);
	void move(const float &dt);
	void update(const float &dt);
	void moveDown(const float &dt);
	bool CheckMoveDownEnd();
	void SetVectorOfMoveDown();
	void moveRight(const float &dt);
	void SetVectorOfMoveRight();
	bool CheckMoveRightEnd();
	void CheckIfItsTimeToChange();
	const sf::Sprite& GetSprite();
	void operator -(const int damage);
	
	int GetGold();

	sf::FloatRect GetGlobalBounds();
	const bool intersectionWithNexus();
	Enemy(sf::Font &Font, int hp, sf::FloatRect NexusPosition);
	~Enemy();
};

