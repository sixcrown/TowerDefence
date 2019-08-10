#ifndef WAVESTATE_H
#define WAVESTATE_H

#include "includes.h"
#include "Enemy.h"

class WaveState
{
private:
	int wave0;
	int Enemies_hp;
	int number_of_enemies;
	sf::Clock *WaveClock;
	sf::Font font;
	sf::Time getStateTime();
public:
	WaveState(int wave);
	void populateWave(std::vector<std::shared_ptr<Enemy>> *a, const sf::FloatRect NexusPosition);
	void initFont();
	void InitWaveInfoFromFile();
	void update(const float &dt);
	void render(sf::RenderWindow* target);
};
//int WaveState::wave0(0);

#endif // !WAVESTATE_H