#include "weapon.h"
#include <cmath>
#include <iostream>

Weapon::Weapon(std::string name, int damage, int ammo, float range, int speed, wType wType, std::string filename):
	Item(WEAPON, name, filename){
	_wType = wType;
	_damage = damage;
	_ammo = ammo;
	_movRange = range;
	_speed = speed;
	_projectile = Projectile(name, damage, damage, "");
}
Weapon::Weapon(std::string name, int damage, int ammo, float range, int speed, int projSpeed, wType wType, std::string filename, std::string projName):
	Item(WEAPON, name, filename){
	_wType = wType;
	_damage = damage;
	_ammo = ammo;
	_movRange = range;
	_speed = speed;
	_projectile = Projectile(name, damage, projSpeed, projName);
}
Weapon::Weapon(std::string name, int damage, int ammo, float range, int speed, wType wType, std::string filename, std::string pickupName, std::string useName):
	Item(WEAPON, name, filename, pickupName, useName){
	_wType = wType;
	_damage = damage;
	_ammo = ammo;
	_movRange = range;
	_speed = speed;
	_projectile = Projectile(name, damage, damage, "");
}
Weapon::Weapon(std::string name, int damage, int ammo, float range, int speed, int projSpeed, wType wType, std::string filename, std::string projName, std::string pickupName, std::string useName):
	Item(WEAPON, name, filename, pickupName, useName){
	_wType = wType;
	_damage = damage;
	_ammo = ammo;
	_movRange = range;
	_speed = speed;
	_projectile = Projectile(name, damage, projSpeed, projName);
}

Weapon::Weapon():
	Item(WEAPON, "DOES NOT EXIST", "Sprites/BLANK.png"){
	_wType = MELEE;
	_damage = 0;
	_ammo = 0;
	_movRange = 0;
	_speed = 0;
}
Weapon::~Weapon(){

}

void Weapon::loadProjIMG(){
	if(this->getWType() == PROJECTILE){
		_projectile.loadIMG();
		_projectile.setScale(.5, .5);
	}
}

/*
Projectile Weapon::getProjectile(){
	return _projectile;
}
*/

float Weapon::getDmg(){
	return _damage;
}
int Weapon::getAmmo(){
	return _ammo;
}
int Weapon::getRange(){
	return _movRange;
}
int Weapon::getSpeed(){
	return _speed;
}

void Weapon::updateDamage(int dmg){
	_damage = dmg;
}
void Weapon::updateAmmo(int ammo){
	_ammo = ammo;
}
void Weapon::updateRange(int range){
	_movRange = range;
}
void Weapon::updateSpeed(int speed){
	_speed = speed;
}

void Weapon::setAttacking(){
	_attacking = true;
}

wType Weapon::getWType(){
	return _wType;
}


inline sf::Vector2f Weapon::getOffsetVector(sf::Vector2f obj1, sf::Vector2f obj2){
	_radians = atan2((obj1.y - obj2.y) , (obj1.x - obj2.x));
	_radians += 0.61086523819801535192277; //35 degrees
	//radians = (radians * 180 / 3.14159265) + 35;
	//radians = radians * 3.14159265 / 180;
	return sf::Vector2f(cos(_radians), sin(_radians));
}

inline sf::Vector2f Weapon::getOffsetVector(float radians, float x, float y){
	radians += 0.61086523819801535192277; //35 degrees
	//radians = (radians * 180 / 3.14159265) + 35;
	//radians = radians * 3.14159265 / 180;
	return sf::Vector2f(cos(radians + x), sin(radians + y));
}

bool Weapon::getAttacking(){
	return _attacking;
}
Projectile Weapon::getProjectile(float xmove, float ymove){
	_projectile.setMove(xmove, ymove);
	_projectile.setPos(sf::Vector2f(_sprite.getPosition().x + (xmove * 90), _sprite.getPosition().y + (ymove * 90)));
	return _projectile;
}

void Weapon::update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads, float mouseAngle){
	/*
	if(_rotating){
		_sprite.rotate(_deg * elapsedTime);
		std::cout << _sprite.getRotation() << std::endl;
		if(_sprite.getRotation() >= (_distance - 1) && _sprite.getRotation() <= (_distance + 1)){
			_rotating = false;
			_sprite.setRotation(0);
		}
	}
	*/
	if(_attacking && (_ranger < _movRange )){
		switch(_wType){
		case MELEE:
			_move.x -= _speed * elapsedTime;
			_move.y -= _speed * elapsedTime;
			_rot -= 100 * elapsedTime;
			_ranger += _speed * elapsedTime;
			break;
		case PROJECTILE:
			break;
		case HITSCAN:
			break;
		default:
			break;
		}
		_timer += elapsedTime;
	}
	else{
		_attacking = false;
		_timer = 0;
		_ranger = 0;
		_move = sf::Vector2f(0, 0);
		_rot = 0;
	}

	_temp = getOffsetVector(rads, _move.x, _move.y);//this

	_sprite.setPosition(sf::Vector2f((pos.x + (size.x * 1.25) * _temp.x) , (pos.y + (size.y * 1.25) * _temp.y) ));
	_sprite.setRotation(mouseAngle + _rot);

}






















