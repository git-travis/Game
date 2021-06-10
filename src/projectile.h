#pragma once
#include "item.h"

#include <iosfwd>

class Projectile: public Item{
public:
	Projectile(std::string name, float dmg, float speed, std::string filename);
	Projectile();
	~Projectile();

	float getDmg();

	void setMove(float x, float y);
	void setDmg(float dmg);

	void update(float elapsedTime);
private:
	sf::Vector2f _xy;
	float _dmg;
	float _speed;

};
