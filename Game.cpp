#include "Game.h"


//Static functions

//initializer functions

void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->fullscreen = false;
}

void Game::initWindow() //creates a sfml window
{
	std::ifstream ifs("Config/window.ini");
	//this->video_modes = sf::VideoMode::getFullscreenModes();
	sf::VideoMode window_bounds= sf::VideoMode::getDesktopMode(); //bounds of the window 
	std::string title = "none";
	unsigned int framerate = 120; //framerate limit
	bool vertical_s_e = false; //vertical sync enabled
	unsigned antialias = 0;
	bool fullscreen = false;
	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate;
		ifs >> vertical_s_e;
		ifs >> antialias;

	}
	this->fullscreen = fullscreen;
	this->window_settings.antialiasingLevel = antialias;
	ifs.close();
	if (this->fullscreen) 
	{
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, window_settings);
	}
	else
	{
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings);
	}
	this->window->setFramerateLimit(framerate);
	this->window->setVerticalSyncEnabled(vertical_s_e);
}

void Game::initStates()
{
	this->states.push(new Main_menu_state(this->window,&this->supportedKeys, &this->states));
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		int kvalue = 0;
		while (ifs >> key >> kvalue)
		{
			this->supportedKeys[key] = kvalue;
		}
	}
	ifs.close();
}




//constructors/destructors
Game::Game()
{
	this->initVariables();
	this->initKeys();
	this->initWindow();
	this->initStates();
}


Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt() //updates dt variable with the time it takes to update and render 1 frame
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication()
{
	std::cout << "ending app" << std::endl;
}

//Functions


void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}
		



void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->quit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else//app end
	{
		this->endApplication();
		this->window->close();
	}
}


void Game::render()
{
	this->window->clear();
	//render now
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}
	this->window->display();
}


void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();

	}
}
