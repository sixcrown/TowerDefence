//#include "Button.h"
//
//
//
//
//
//
//Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
//{
//	this->buttonState = B_IDLE;
//	this->shaperinho.setPosition(sf::Vector2f(x, y));
//	this->shaperinho.setSize(sf::Vector2f(width, height));
//
//	this->font = font;
//	this->text.setFont(*this->font);
//	this->text.setString(text);
//	this->text.setFillColor(sf::Color::Magenta);
//	this->text.setCharacterSize(20);
//
//	this->text.setPosition(
//		this->shaperinho.getPosition().x + this->shaperinho.getGlobalBounds().width/2 - this->text.getGlobalBounds().width/2.f,
//		this->shaperinho.getPosition().y + this->shaperinho.getGlobalBounds().height/2 - this->text.getGlobalBounds().height / 2.f
//	);
//
//	this->idleColor = idleColor;
//	this->hoverColor = hoverColor;
//	this->activeColor = activeColor;
//
//	this->shaperinho.setFillColor(this->idleColor);
//}
//
//Button::~Button()
//{
//}
//const bool Button::isPressed() const
//{
//	if (this->buttonState == B_PRESSED)
//		return true;
//	return false;
//}
////accessors
//
////functions
//void Button::update(const sf::Vector2f &mousePos)
//{
//	//update bools for hover and press
//	this->buttonState = B_IDLE;
//	if (this->shaperinho.getGlobalBounds().contains(mousePos))
//	{
//		this->buttonState = B_HOVER;
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			this->buttonState = B_PRESSED;
//		}
//	}
//	switch (this->buttonState)
//	{
//	case B_IDLE:
//		this->shaperinho.setFillColor(this->idleColor);
//			break;
//	case B_HOVER:
//		this->shaperinho.setFillColor(this->hoverColor);
//			break;
//	case B_PRESSED:
//		this->shaperinho.setFillColor(this->activeColor);
//			break;
//	default:
//		this->shaperinho.setFillColor(sf::Color::Blue);
//		break;
//	}
//}
//
//void Button::render(sf::RenderTarget * target)
//{
//	target->draw(this->shaperinho);
//	target->draw(this->text);
//}
