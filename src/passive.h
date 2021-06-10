#pragma once
#include "item.h"

class Passive: public Item{
public:
	Passive(apType pType, std::string name, int damage, int heal, int speed, std::string filename);
	Passive();
	virtual ~Passive();

	void updateDamage(int damage);
	void updateHeal(int heal);
	void updateSpeed(int speed);

	int getAddDmg();
	int getMultDmg();
	int getHeal();
	int getSpeed();

	void update(float elapsedTime, sf::Vector2f pos);
private:
	apType _pType;

	int _damageAMT = 0;
	int _multDmg = 0;
	int _healAMT = 0;
	int _speedMOD = 0;
};
