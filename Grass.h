#pragma once
#include "includes.h"
#include "TIle.h"
class Grass
{
	sf::Sprite background;
	sf::Texture backgroundTexture;


public:
	void GetfromFile();
	sf::FloatRect GetLocalBounds();
	const bool contain(const sf::Vector2f& a);
	void render(sf::RenderWindow* target);
	Grass();
	~Grass();
};

