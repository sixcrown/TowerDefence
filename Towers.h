#ifndef TOWERS_H
#define TOWERS_H


class Towers
{
private:
//	sf::Sprite texture;
	int attack_damage;
	int range;
	int cost;

public:
	Towers();
	virtual ~Towers();
};

#endif // !TOWERS_H