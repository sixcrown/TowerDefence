#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "includes.h"
#include "State.h"
#include "WaveState.h"
#include "Grass.h"
#include "BuildingMenu.h"
#include "GUI.h"
#include "Road.h"
#include "Player.h"
#include "TIle.h"
#include "Enemy.h"
#include "Collision_Manager.h"
#include "Bullet.h"
#include "WaveState.h"
enum status{IDLE,BUILDING};
class GameState :
	public State
{
private:
	Collision_Manager Manager;
	Road droga;
	std::vector<std::shared_ptr<Enemy>> enemies;
	WaveState *wave;
	Player *player;
	short status;
	Grass grass;
	sf::Clock *GameStateClock;
	sf::Time BeforeWaveTime;
	BuldingMenu *menu;
	std::unique_ptr<gui::HP_BAR> hp;
	std::unique_ptr<gui::CoinIndicator> gold;
	std::vector<std::shared_ptr<Tower>> vTowers;
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::VideoMode video;
	sf::Font font;
	//functions 
	void initKeybinds();
	bool is_button_pressed;
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states);
	virtual ~GameState();
	//Functions
	void initBeforeWaveTime();
	sf::Time getStateTime();
	void endState();
	void update(const float &dt);
	void render(sf::RenderWindow* target = nullptr);
	void updateInput(const float &dt);
	void initBuildingMenu();
	void initFonts();
	void initHP();
	void initGold();
	void updateBuildingMenu();
	std::shared_ptr<Tower> BuildAdequateTower(std::string a, sf::Sprite b);
};

#endif // !GAMESTATE_H
