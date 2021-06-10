#pragma once
#include "rectIMG.h"
#include "ability.h"
#include "passive.h"
#include "shield.h"
#include "weapon.h"
#include "health.h"
#include "consumable.h"
#include "shooter.h"

#include <iosfwd>

class Player: public rectIMG{
public:
	Player(std::string name, std::string filename);
	Player();
	virtual ~Player();

	bool isAlive();

	void update(float elapsedTime, sf::Vector2f pos, sf::Vector2f obj, float rad, float mouseAngle);
	float hurt(float amount);
	void die();
	void pickUp();
	void drop();
	void attack();
	void triggerAbility();

	void move(sf::Vector2f move, float elapsedTime);

	bool getAttacking();

	void setAbility(Ability* ability);
	void setPassive(Passive* passive);
	void setShield(Shield* shield);
	void setWeapon(Weapon* weapon);
	void setHealth(Health* health);
	void setConsumable(Consumable* consumable);

	Ability getAbility();
	Passive getPassive();
	Shield getShield();
	Weapon getWeapon();
	Health getHealth();
	Consumable getConsumable();
	Projectile getProjectile(sf::Vector2f move);

	Item getDrop(itemType type);


	sf::Sprite getAbilitySprite();
	sf::Sprite getPassiveSprite();
	sf::Sprite getShieldSprite();
	sf::Sprite getWeaponSprite();
	sf::Sprite getHealthSprite();
	sf::Sprite getConsumableSprite();

	std::vector<sf::Sprite> getSpawnables();

private:
	bool _alive = true;

	std::string _name;

	Ability* _ability;
	Passive* _passive;
	Shield* _shield = new Shield("Basic", 100, "Sprites/Shield_High.png");
	Weapon* _weapon;
	Health* _health = new Health("Health100", 100, "Sprites/Heart_High.png");
	Consumable* _consumable = new Consumable("Insta-Health", "Sprites/Health_Bandaid.png");

	std::vector<sf::Sprite> _spawnables;


};
