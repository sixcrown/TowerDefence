#include "includes.h"
#include "BuildingMenu.h"

BuldingMenu::BuldingMenu(sf::VideoMode& vm, sf::Font &font)
{
	this->font = &font;
	auto p = sf::Vector2f(
		static_cast<float>(vm.width) / 8.f,
		static_cast<float>(vm.height) - gui::p2pY(9.3f, vm)
	);
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 10.f,
			static_cast<float>(vm.height)/3.3f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 50));
	this->container.setPosition(
		static_cast<float>(vm.width) - this->container.getSize().x,
		0.f
	);
	if (&font) 
	{
		this->menuText.setFont(font);
		this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
		this->menuText.setCharacterSize(gui::calcCharSize(vm));
		this->menuText.setString("BUILD");
		this->menuText.setPosition(
			this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
			this->container.getPosition().y);
	}
	
}

BuldingMenu::~BuldingMenu()
{
}


std::map<std::string, std::shared_ptr<gui::ButtonBuildingMenu>>& BuldingMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool BuldingMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void BuldingMenu::addButton(
	const std::string key,
	float yy,
	const unsigned char_size,
	const std::string text)
{
	auto x =  this->container.getPosition().x;
	auto y =  yy + this->container.getPosition().y;
	this->buttons[key] = std::make_shared<gui::ButtonBuildingMenu>(
		x, y,
		this->font, text, char_size,
		sf::Color(255, 215, 0), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),key
		);
}

void BuldingMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void BuldingMenu::render(sf::RenderTarget * target)
{
	target->draw(this->container);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target->draw(this->menuText);
}

float BuldingMenu::GetTextYAxis()
{
	return this->menuText.getGlobalBounds().height;
}

float BuldingMenu::Get_y_Axis()
{
	return this->container.getPosition().y;
}

sf::Vector2f BuldingMenu::getContainerSize()
{
	return sf::Vector2f(this->container.getSize());
}

