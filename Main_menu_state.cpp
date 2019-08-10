#include "Main_menu_state.h"




void Main_menu_state::initBackground()
{
	/*this->background.setSize(sf::Vector2f
	(static_cast<float>(this->window->getSize().x),
	static_cast<float>(this->window->getSize().y)));*/
	this->background.setSize(sf::Vector2f(800,600));
	
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Tiles/BadGuysWhite.png"))
	{
		throw"ERROR:MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void Main_menu_state::initVariables()
{
}

void Main_menu_state::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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
	/*this->keyBinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keyBinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keyBinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keyBinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keyBinds["MOVE_DOWN"] = this->supportedKeys->at("S");*/
}

void Main_menu_state::initFonts()
{
	try
	{
		if (!this->font.loadFromFile("Fonts/Beyond Wonderland.ttf"))
		{
			throw(20);
			//throw("ERROR:MAINMENUSTATE::Couldnt load font Beyond Wonderland");
		}
	}
	catch (int e)
	{
		std::cout << e;
	}


}

void Main_menu_state::initButtons()
{
	auto vm = sf::VideoMode(1024, 768);
	this->buttons["GAME_STATE"] = new gui::ButtonMenu(
		gui::p2pX(15.6f, vm), gui::p2pY(20.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	this->buttons["EXIT_STATE"] = new gui::ButtonMenu(
		gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}



void Main_menu_state::updateButtons()
{
	//auto it = this->buttons.begin();
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	//this->gamestatebutton->update(this->mousePosView);
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys,this->states));
	}
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->wanna_end = true;
	}
}

void Main_menu_state::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

Main_menu_state::Main_menu_state(sf::RenderWindow* window, std::map<std::string, int>*supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}


Main_menu_state::~Main_menu_state()
{
	
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	//delete this->gamestatebutton;
}

void Main_menu_state::endState()
{
	std::cout << "Ending main menu STATE!!!" << std::endl;
}

void Main_menu_state::update(const float &dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons();
	//system("cls");
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
	

}

void Main_menu_state::render(sf::RenderWindow *target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(target);
}

void Main_menu_state::updateInput(const float & dt)
{
	this->checkForEnd();
}
