#include "Grass.h"



void Grass::GetfromFile()
{
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/tiles.png"))
	{
		throw"ERROR:MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(this->backgroundTexture,false);
}

sf::FloatRect Grass::GetLocalBounds()
{
	return this->background.getLocalBounds();
}

const bool Grass::contain(const sf::Vector2f& a)
{
	if (this->GetLocalBounds().contains(a)) return true;
		return false;
}

void Grass::render(sf::RenderWindow* target)
{
	target->draw(this->background);
}

Grass::Grass()
{
	this->GetfromFile();
}


Grass::~Grass()
{
}
