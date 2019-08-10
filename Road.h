#pragma once
#include "includes.h"
#include "TIle.h"
#include "Enemy.h"
class Road
{
private:
	sf::FloatRect NexusPosition;
	std::vector<std::shared_ptr<Tiles>> Voftiles;
	std::vector<std::shared_ptr<Tower>> VofTowers;
	std::map<std::string, sf::Texture*> MapOfTextures;
	float x; //number of elements on the X-axis
	float y; //number of elements on the Y-axis
	float sizeX; // size of 1 tile on X-axis
	float sizeY; //size of 1 tile on Y-axis
public:
	Road();
	~Road();
	void GetMapFromFile();
	void InitMapOfTextures();
	void render(sf::RenderTarget *target);
	std::vector<std::shared_ptr<Tower>> ReturnTowers();
	void SearchForNexusPosition();
	const sf::FloatRect ReturnNexusPosition();
};
struct EnemyMovement
{
	sf::FloatRect tile;
	short direction;

};

