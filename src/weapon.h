#pragma once
#include "item.h"
#include "projectile.h"

#include <iosfwd>

class Weapon: public Item{
public:
	Weapon(std::string name, int damage, int ammo, float range, int speed, wType wType, std::string filename);
	Weapon(std::string name, int damage, int ammo, float range, int speed, int projSpeed, wType wType, std::string filename, std::string projName);
	Weapon(std::string name, int damage, int ammo, float range, int speed, wType wType, std::string filename, std::string pickupName, std::string useName);
	Weapon(std::string name, int damage, int ammo, float range, int speed, int projSpeed, wType wType, std::string filename, std::string projName, std::string pickupName, std::string useName);
	Weapon();
	virtual ~Weapon();

	float getDmg();

	int getAmmo();
	int getRange();
	int getSpeed();

	void updateDamage(int dmg);
	void updateAmmo(int ammo);
	void updateRange(int range);
	void updateSpeed(int speed);

	void loadProjIMG();

	void setAttacking();
	bool getAttacking();

	void update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads, float mouseAngle);

	inline sf::Vector2f getOffsetVector(sf::Vector2f obj1, sf::Vector2f obj2);
	inline sf::Vector2f getOffsetVector(float radians, float x, float y);

	Projectile getProjectile(float xmove, float ymove);

	wType getWType();
private:
	bool _attacking = false;

	int _damage;
	int _ammo;
	int _speed = 1;

	float _movRange = 0;
	float _ranger = 0;
	float _time = 1;
	float _timer = 0;
	float _rot = 0;
	float _radians = 0;

	sf::Vector2f _move = sf::Vector2f(0, 0);
	sf::Vector2f _temp;

	Projectile _projectile;

	wType _wType;
};
