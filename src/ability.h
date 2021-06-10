#pragma once
#include "item.h"

#include <iosfwd>

class Ability: public Item{
public:
	Ability(apType aType, std::string name, int damage, int heal, int speed, float time, std::string filename);
	Ability(apType aType, aMoveType amType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string spawnableName);
	Ability(apType aType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string pickupName, std::string useName);
	Ability(apType aType, aMoveType amType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string spawnableName, std::string pickupName, std::string useName);
	Ability();
	virtual ~Ability();

	void loadAbility();

	bool offCooldown();
	void coolDown();

	void updateDamage(int damage);
	void updateHeal(int heal);
	void updateSpeed(int speed);
	void setAmtUsed(int amtUsed);
	void setTelePos(sf::Vector2f pos);

	int getAddDmg();
	int getMultDmg();
	int getHeal();
	int getSpeed();
	int getAmtUsed();
	sf::Vector2f getTelePos();

	apType getAType();
	aMoveType getAMType();

	sf::Sprite getSpawnable();
	void loadSpawnable();

	void update(float elapsedTime, sf::Vector2f pos);
private:
	apType _aType;
	aMoveType _amType;
	bool _onCD = false;
	bool _hasSpawn = false;

	int _damageAMT = 0;
	int _multDmg = 0;
	int _healAMT = 0;
	int _speedMOD = 0;
	int _amtUsed = 0;

	float _cooldownTimer = 0;
	float _cooldownTime;

	rectIMG _spawnable;

	sf::Vector2f _telePos = sf::Vector2f(0, 0);

};
