#include "GameState.h"



void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string kkey = "";
		while (ifs >> key >> kkey)
		{
			this->keyBinds[key] = this->supportedKeys->at(kkey);
		}
	}
	ifs.close();
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->wave = new WaveState(0);
	this->Manager.Enemies = &enemies;
	this->status = IDLE;
	this->droga;
	this->vTowers = this->droga.ReturnTowers();
	this->Manager.Towers = &this->vTowers;
	this->video = sf::VideoMode(this->window->getSize().x, this->window->getSize().y);
	this->is_button_pressed = false;
	this->wanna_end = false;
	this->game_is_on = true;
	std::cout << "tutaj gamestate" << std::endl;
	this->initFonts();
	this->BeforeWaveTime = sf::seconds(3);
	this->initBeforeWaveTime();
	this->initKeybinds();
	this->initBuildingMenu();
	this->initHP();
	this->initGold();
	this->player = new Player();
	this->Manager.bullets = &this->bullets;
}


GameState::~GameState()
{
	delete this->player;
	delete this->GameStateClock;
	delete this->menu;
	for (auto it : this->vTowers)
	{
		this->vTowers.pop_back();
	}
	for (auto it : this->bullets)
	{
		this->bullets.pop_back();
	}
	for (auto it : this->enemies)
	{
		enemies.pop_back();
	}
	delete this->wave;
}


void GameState::initBeforeWaveTime()
{
	{
		if (this->GameStateClock)
		{
			delete this->GameStateClock;
			this->GameStateClock = new sf::Clock;
			this->GameStateClock->restart();
		}
		else {
			this->GameStateClock = new sf::Clock;
			this->GameStateClock->restart();
		}
	}
}

sf::Time GameState::getStateTime()
{
	return this->GameStateClock->getElapsedTime();
}

void GameState::endState()
{

	if (this->wanna_end) 
	{
		this->initBeforeWaveTime();
		std::cout << "Ending game STATE!!!" << std::endl;
		this->wanna_end = true;
	}
}

void GameState::update(const float &dt)
{
	this->wave->populateWave(&this->enemies,this->droga.ReturnNexusPosition());
	for (auto it : this->enemies)
	{
		it->update(dt);
	}
	for (auto it : this->bullets)
	{
		it->update(dt);
	}
	this->Manager.CheckTowerEnemyCollision();
	this->Manager.CheckForBulletsToDelete();
	this->Manager.DeleteIntersectingBullets();
	this->player->getGoldFromMonster(this->Manager.checkForEnemyDeletion());
	this->player->LoseHp(this->Manager.CheckForNexusIntersection());
	this->menu->update(this->mousePosWindow);
	this->updateInput(dt);
	this->player->getGoldFromTimePassed(this->GameStateClock);
	if (this->player->GetCurrentHp() <= 0)
	{
		this->wanna_end = true;
	}
	
}

void GameState::render(sf::RenderWindow* target)
{

	if (!target)
		target = this->window;
	this->grass.render(this->window);
	this->menu->render(this->window);
	this->hp->render(this->window);
	this->gold->render(target);
	this->droga.render(target);
	for (auto it : this->enemies)
	{
		it->render(target);
	}
	for (auto it : this->vTowers)
	{
		it->render(target);
	}
	for (auto it : this->bullets)
	{
		it->render(target);
	}
	
}

void GameState::updateInput(const float & dt)
{
	this->endState();
	this->checkForEnd();
	this->updateMousePositions();
	this->updateBuildingMenu();
	this->hp->update(this->player->GetCurrentHp());
	this->gold->update(this->player->GetCurrentGold());
}

void GameState::initBuildingMenu()
{
	this->menu = new BuldingMenu(this->video,this->font);
	this->menu->addButton("Fire", this->menu->GetTextYAxis(),  gui::calcCharSize(this->video), "10");
	this->menu->addButton("Lightning", this->menu->GetTextYAxis(), gui::calcCharSize(this->video), "100");
	this->menu->addButton("Light", this->menu->GetTextYAxis(), gui::calcCharSize(this->video), "150");
	this->menu->addButton("Arrow", this->menu->GetTextYAxis(), gui::calcCharSize(this->video), "200");
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Oswald.ttf"))
	{
		throw("ERROR:MAINMENUSTATE::Couldnt load font Beyond Wonderland");
	}

}

void GameState::initHP()
{
	this->hp = std::make_unique<gui::HP_BAR>((int)20, this->font, this->video);
}

void GameState::initGold()
{
	this->gold = std::make_unique<gui::CoinIndicator>((int)100, this->font, this->video);
}

void GameState::updateBuildingMenu()
{
	auto i = this->menu->getButtons();
	std::shared_ptr<gui::ButtonBuildingMenu> tmp2;
	std::string tmp1;
	switch (status) 
	{
	case IDLE:
	{
		for (auto it : i)
		{
			if (it.second->isPressed())
			{
				if (it.second->getCost() > this->player->GetCurrentGold())
				{
					std::cout << "Insufficient Resources" << std::endl;
				}
				else
				{
					this->status = BUILDING;
				}
			}
		}
	}
		 break;
	case BUILDING:
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			std::cout << "Building Ended" << std::endl;
			this->status = IDLE;
		}
		else
		{
			for (auto it : this->vTowers)
			{
				if (it->isClicked(static_cast<sf::Vector2f>(this->mousePosWindow)))
				{
					for (auto it : i)
					{
						if (it.second->wasPressed())
						{
							tmp1 = it.first;
							tmp2 = it.second;
						}
					}
					if (it->getType() == "empty")
					{
						tmp2->setPressAfterSuccessfullTransaction();
						this->player->LoseGoldFromBuying(tmp2->getCost());
						auto p = this->BuildAdequateTower(tmp1, it->getShape());
						this->vTowers.push_back(p);
						this->vTowers.erase(std::remove(this->vTowers.begin(), this->vTowers.end(), it), this->vTowers.end());
						this->status = IDLE;
						break;
					}
					else if (it->getType() == tmp1)
					{
						if (it->getLevel() != 3) 
						{
							tmp2->setPressAfterSuccessfullTransaction();
							this->player->LoseGoldFromBuying(tmp2->getCost());
							it->update();
							this->status = IDLE;
						}
					}
				}
			}
		}
		break;
	}
}

std::shared_ptr<Tower>GameState::BuildAdequateTower(std::string a, sf::Sprite b)
{
	if (a == "Fire")
	{
		auto tmp = std::make_shared<FireTower>(b);
		return tmp;
	}
	else if (a == "Light")
	{
		auto tmp = std::make_shared<LightTower>(b);
		return tmp;
	}
	else if (a == "Lightning")
	{
		auto tmp = std::make_shared<LightningTower>(b);
		return tmp;
	}
	else 
	{
		auto tmp = std::make_shared<ArrowTower>(b);
		return tmp;
	}
}
