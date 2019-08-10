#include "includes.h" 
#include "Gui.h"

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the x-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the y-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	/*
	 * Calculates the character size for text using the current resolution and a constant.
	 *
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 * @param		unsigned modifier		Used to modify the character size in a more custom way.
	 *
	 * @return		unsigned				The calculated character size value.
	 */

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::ButtonMenu::ButtonMenu(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;
	this->press = false;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}



//Accessors
 bool gui::Buttons::isPressed() 
{
	if (this->buttonState == BTN_ACTIVE) 
	{
		this->press = true;
		return true;
	}
	this->press = false;
	return false;
}

 bool gui::Buttons::wasPressed()
 {
	 if (this->press)
	 {
		 return true;
	 }
	 return false;
 }

 void gui::Buttons::setPressAfterSuccessfullTransaction()
 {
	 this->press = false;
 }

const std::string gui::Buttons::getText() const
{
	return this->text.getString();
}

const short unsigned & gui::Buttons::getId() const
{
	return this->id;
}

//Modifiers
void gui::Buttons::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Buttons::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::ButtonMenu::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::ButtonMenu::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
gui::Buttons::~Buttons()
{

}
gui::ButtonMenu::~ButtonMenu()
{

}



gui::ButtonBuildingMenu::ButtonBuildingMenu(float x, float y,
	sf::Font * font, std::string text, unsigned character_size, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, std::string which, short unsigned id)
{
	this->cost =std::stoi(text);
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->initButtonTexture();
	this->GetTextureRect(which);
	this->SetTextureRect();

	this->BMENU_button.setPosition(x+this->bounds.left, y+this->bounds.top);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->BMENU_button.getPosition().x + (this->BMENU_button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->BMENU_button.getPosition().y + (this->BMENU_button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);


	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;
}

void gui::ButtonBuildingMenu::GetTextureRect(std::string a)
{
	std::fstream file;
	file.open("Config/TowersTextureCoordinates.ini");
		if (!file.is_open()) 
		{ 
			throw("BUTTONBUILDINGMENU::COULDNT LOAD TowerTextureCoordinates.ini");
		}
		file >> this->bounds.width;
		file >> this->bounds.height;
		std::string tmp;
		while (file >> tmp)
		{
			if (tmp == a)
			{
				file>>this->bounds.left;
				file>>this->bounds.top;
			}
		}
		file.close();
}

void gui::ButtonBuildingMenu::SetTextureRect()
{
	this->BMENU_button.setTextureRect(this->bounds);
}

void gui::ButtonBuildingMenu::initButtonTexture()
{
	if (!this->BMENU_texture.loadFromFile("Resources/Images/Backgrounds/BMtowers.png"))
	{
		throw("ERROR:GUI::BUTTONBUILDINGMENU::Couldnt load tiles of buttons in building menu");
	}
	this->BMENU_button.setTexture(this->BMENU_texture);
	//this->BMENU_button.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(50, 100)));

}

void gui::ButtonBuildingMenu::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->BMENU_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void gui::ButtonBuildingMenu::render(sf::RenderTarget * target)
{
	target->draw(this->BMENU_button);
	target->draw(this->text);
}

float gui::ButtonBuildingMenu::getXbounds()
{
	return static_cast<float>(this->bounds.left);
}

float gui::ButtonBuildingMenu::getYbounds()
{
	return static_cast<float>(this->bounds.top);
}

int gui::ButtonBuildingMenu::getCost()
{
	return this->cost;
}

gui::HP_BAR::HP_BAR(int max_value, sf::Font &font,sf::VideoMode &vm)
{
	this->initTexture();
	this->max_value = max_value;
	this->texture.setTexture(loadTexture);

	this->texture.setPosition(gui::p2pX(85.f,vm), gui::p2pY(0.f, vm));
	if(&font)
	{
		this->text.setCharacterSize(17);
		this->text.setFont(font);
		this->text.setFillColor(sf::Color::Black);
		this->text.setOutlineColor(sf::Color::Green);
		this->Hp_text = std::to_string(max_value) + "/" + std::to_string(max_value);
		this->text.setString(this->Hp_text);
	}
	this->text.setPosition(
		this->texture.getPosition().x + (this->texture.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->texture.getPosition().y + (this->texture.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f+gui::p2pY(1.f,vm)
	);
}

void gui::HP_BAR::update(const int current_value)
{
	this->Hp_text = std::to_string(current_value) + "/" + std::to_string(this->max_value);
	this->text.setString(this->Hp_text);
}


void gui::PlayerGui::render(sf::RenderTarget * target)
{
	target->draw(this->texture);
	target->draw(this->text);
}

void gui::HP_BAR::initTexture()
{
	if (!this->loadTexture.loadFromFile("Resources/Images/Backgrounds/HP.png")) throw("HPBAR::COULDNT LOAD HP.PNG");
}

void gui::CoinIndicator::initTexture()
{
	if (!this->loadTexture.loadFromFile("Resources/Images/Backgrounds/Coins.png")) throw("HPBAR::COULDNT LOAD HP.PNG");
}
gui::CoinIndicator::CoinIndicator(int max_value, sf::Font &font, sf::VideoMode &vm)
{
	this->initTexture();
	this->max_value = max_value;
	this->texture.setTexture(loadTexture);

	this->texture.setPosition(gui::p2pX(79.f, vm), gui::p2pY(0.f, vm));
	if (&font)
	{
		this->text.setCharacterSize(25);
		this->text.setFont(font);
		this->text.setFillColor(sf::Color(255, 215, 0));
		this->text.setOutlineColor(sf::Color::Green);
		this->Hp_text = std::to_string(max_value);
		this->text.setString(this->Hp_text);
	}
	this->text.setPosition(
		this->texture.getPosition().x + (this->texture.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->texture.getPosition().y + (this->texture.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f + gui::p2pY(8.f, vm)
	);
}
void gui::CoinIndicator::update(const int current_value)
{
	this->Hp_text = std::to_string(current_value);
	this->text.setString(this->Hp_text);
}