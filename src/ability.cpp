#include "ability.h"
#include <iostream>

Ability::Ability(apType aType, std::string name, int damage, int heal, int speed, float time, std::string filename):
	Item(ABILITY, name, filename){
	_aType = aType;
	_damageAMT = damage;
	_healAMT = heal;
	_speedMOD = speed;
	_cooldownTime = time;
	_amType = NOTM;
}
Ability::Ability(apType aType, aMoveType amType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string spawnableName):
	Item(ABILITY, name, filename){
	_aType = aType;
	_damageAMT = damage;
	_healAMT = heal;
	_speedMOD = speed;
	_cooldownTime = time;
	_amType = amType;
	_spawnable = rectIMG(spawnableName);
	_hasSpawn = true;
}
Ability::Ability(apType aType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string pickupName, std::string useName):
	Item(ABILITY, name, filename, pickupName, useName){
	_aType = aType;
	_damageAMT = damage;
	_healAMT = heal;
	_speedMOD = speed;
	_cooldownTime = time;
	_amType = NOTM;
}
Ability::Ability(apType aType, aMoveType amType, std::string name, int damage, int heal, int speed, float time, std::string filename, std::string spawnableName, std::string pickupName, std::string useName):
	Item(ABILITY, name, filename, pickupName, useName){
	_aType = aType;
	_damageAMT = damage;
	_healAMT = heal;
	_speedMOD = speed;
	_cooldownTime = time;
	_amType = amType;
	_spawnable = rectIMG(spawnableName);
	_hasSpawn = true;
}
Ability::Ability():
	Item(ABILITY, "EMPTY", "Sprites/BLANK.png"){
	_aType = HEAL;
}

Ability::~Ability(){
}

void Ability::loadAbility(){
	loadIMG();
	if(_hasSpawn){
		_spawnable.loadIMG();
	}
}

void Ability::updateDamage(int damage){
	_damageAMT = damage;
}
void Ability::updateHeal(int heal){
	_healAMT = heal;
}
void Ability::updateSpeed(int speed){
	_speedMOD = speed;
}
void Ability::setTelePos(sf::Vector2f pos){
	_telePos = pos;
}
void Ability::setAmtUsed(int amtUsed){
	_amtUsed = amtUsed;
}

int Ability::getAddDmg(){
	return _damageAMT;

}
int Ability::getMultDmg(){
	return _multDmg;
}
int Ability::getHeal(){
	return _healAMT;
}
int Ability::getSpeed(){
	return _speedMOD;
}
int Ability::getAmtUsed(){
	return _amtUsed;
}
sf::Vector2f Ability::getTelePos(){
	return _telePos;
}

apType Ability::getAType(){
	return _aType;
}
aMoveType Ability::getAMType(){
	return _amType;
}
bool Ability::offCooldown(){
	return !_onCD;
}
void Ability::coolDown(){
	_onCD = true;
}

sf::Sprite Ability::getSpawnable(){
	return _spawnable.getSprite();
}

void Ability::loadSpawnable(){
	_spawnable.loadIMG();
}

void Ability::update(float elapsedTime, sf::Vector2f pos){
	//_sprite.setPosition(sf::Vector2f(pos.x + (size.x * 1.5) * -obj.x, pos.y + (size.y * 1.5) * -obj.y));
	setPos(pos);
	if(_onCD && (_cooldownTimer < _cooldownTime)){
		_cooldownTimer += elapsedTime;
	}
	else{
		_onCD = false;
		_cooldownTimer = 0;
	}


}

