#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include"Gui.h"

class Gui;

class BuldingMenu
{
private:
	sf::Text menuText;
	sf::RectangleShape container;
	sf::Font *font;
	std::map<std::string, std::shared_ptr<gui::ButtonBuildingMenu>> buttons;


public:
	BuldingMenu(sf::VideoMode& vm,sf::Font &font);
	~BuldingMenu();
	//Accessor
	std::map<std::string, std::shared_ptr<gui::ButtonBuildingMenu>>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,
		float yy,
		const unsigned char_size,
		const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget* target);
	float GetTextYAxis();
	float Get_y_Axis();
	sf::Vector2f getContainerSize();

	

};

#endif