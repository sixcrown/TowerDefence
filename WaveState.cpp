#include "WaveState.h"




sf::Time WaveState::getStateTime()
{
	return this->WaveClock->getElapsedTime();
}

WaveState::WaveState(int wave)
{
	this->Enemies_hp = 0;
	this->number_of_enemies = 0;
	this->wave0 = wave;
	this->initFont();
}

void WaveState::populateWave(std::vector<std::shared_ptr<Enemy>> *a, const sf::FloatRect NexusPosition)
{

	if (a->empty()) 
	{
		this->wave0++;
		this->InitWaveInfoFromFile();
		for (auto it = 0; it < number_of_enemies; it++)
		{
			a->emplace_back(std::make_shared<Enemy>(this->font, Enemies_hp,NexusPosition));
		}
	}
}

void WaveState::initFont()
{
	if (!this->font.loadFromFile("Fonts/Oswald.ttf"))
	{
		throw("ERROR:MAINMENUSTATE::Couldnt load font Beyond Wonderland");
	} 
}

void WaveState::InitWaveInfoFromFile()
{
	
	std::fstream file;
	file.open("Config/WaveInfo.ini");
	for (int i = 0; i < wave0; i++)
	{
		file >> Enemies_hp;
		file >> number_of_enemies;
	}
	file.close();
}

void WaveState::update(const float &dt)
{
}

void WaveState::render(sf::RenderWindow* target)
{
}



