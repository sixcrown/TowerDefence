#include "State.h"

State::State(sf::RenderWindow * window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states)
{
	this->states = states;
	this->window = window;
	this->wanna_end = false;
	this->supportedKeys = supportedKeys;
}

State::~State()
{
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::checkForEnd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->wanna_end =true;
	}
}

const bool & State::quit() const
{
	return this->wanna_end;
}


