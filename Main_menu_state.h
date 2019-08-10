#ifndef MAINMENUSTATE
#define MAINMENUSTATE

#include "GameState.h"
#include "Button.h"
#include "GUI.h"
class Main_menu_state :
	public State
{

private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	//Button *gamestatebutton;
	std::map<std::string, gui::ButtonMenu*> buttons;

	void initVariables();
	void initKeybinds();
	void initFonts();
	void initButtons();
	void initBackground();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);
	
public:
	Main_menu_state(sf::RenderWindow* window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states);
	virtual ~Main_menu_state();

	void endState();
	void update(const float &dt);
	void render(sf::RenderWindow* target);
	void updateInput(const float &dt);
};

#endif // !MAINMENUSTATE