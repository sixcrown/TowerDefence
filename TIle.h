#ifndef TILE_H
#define TILE_H
#include "includes.h"
#include "CollisionCircle.h"
class Tiles
{
private:

protected:
	sf::Sprite shape;
	std::string type;
public:
	Tiles();
	Tiles(int x, int y, const sf::Texture *texture, std::string type);
	virtual ~Tiles();

	const std::string& getType() const;
	const sf::Sprite& getShape() const;

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	virtual void update();
	virtual void render(sf::RenderTarget *target, const sf::Vector2f player_position = sf::Vector2f());
};
class Nexus:public Tiles
{
	Nexus();
	Nexus(sf::Sprite a);
};
class Tower: public Tiles
{
protected:
	sf::Clock *ShootClock;
	float ShootCooldown;
	sf::IntRect bounds;
	int range;
	int damage;
	int level;
	float BulletMovementSpeed;
	sf::Sprite Display;
	sf::Texture texture;
	CollisionCircle *circle;
public:
	Tower();
	Tower(sf::Sprite a);
	const bool& isClicked(const sf::Vector2f& MousePos) const;
	void initTowerDisplayInfo();
	void initCollisionCircle();
	void initShootClock();
	bool CheckIfItsTimeToShoot();
	void redrawCollisionCircle();
	const float getBulletMovementSpeed();
	const int getTowerDamage();
	int getLevel();
	CollisionCircle GetCircle();
};
class FireTower : public Tower
{
private:
	void initTexture();
public:
	FireTower(sf::Sprite a);
	virtual void render(sf::RenderTarget *target, const sf::Vector2f player_position = sf::Vector2f()) override;
	virtual void update() override;
	~FireTower();
};
class LightningTower : public Tower
{
private:
	void initTexture();
public:
	LightningTower(sf::Sprite a);
	virtual void render(sf::RenderTarget *target, const sf::Vector2f player_position = sf::Vector2f()) override;
	virtual void update() override;
	~LightningTower();
};
class ArrowTower : public Tower
{
private:
	void initTexture();
public:
	ArrowTower(sf::Sprite a);
	virtual void render(sf::RenderTarget *target, const sf::Vector2f player_position = sf::Vector2f()) override;
	virtual void update() override;
	~ArrowTower();
};
class LightTower : public Tower
{
private:
	void initTexture();
public:
	LightTower(sf::Sprite a);
	virtual void render(sf::RenderTarget *target, const sf::Vector2f player_position = sf::Vector2f()) override;
	virtual void update() override;
	~LightTower();
};

class OtherTiles: public Tiles
{

};
#endif