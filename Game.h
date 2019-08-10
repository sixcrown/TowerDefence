#ifndef GAME_H
#define GAME_H
#include "includes.h"
#include "State.h"
#include "Main_menu_state.h"


class Game
{
private:

	sf::RenderWindow *window;
	sf::Event sfEvent;
	float dt;
	sf::Clock dtClock;
	std::stack<State*> states;

	sf::ContextSettings window_settings;
	bool fullscreen;

	std::map<std::string, int> supportedKeys;


	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();
public:

	//constructors/destructors
	Game();
	virtual ~Game();
	void updateDt();
	void endApplication();
	void updateSFMLEvents();
	void update();


	void render();
	void run();
};

#endif