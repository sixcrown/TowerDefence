#ifndef STATE_H
#define STATE_H
#include "includes.h"
class State
{
private:
protected:
	std::stack<State*>* states;

	sf::RenderWindow* window;

	std::map<std::string, int>*supportedKeys;
	std::map<std::string, int> keyBinds;

	bool game_is_on;
	bool wanna_end; // if u want to end a state

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//RESOURCES
	//std::vector<sf::Texture*> textures;

	//functions

	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states);
	virtual ~State();
	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void update(const float &dt) = 0;
	virtual  void render(sf::RenderWindow* target = nullptr) = 0;
	virtual void checkForEnd();
	const bool& quit() const; //returns whether u want to quit a state
	virtual void updateInput(const float &dt) = 0;
};

#endif