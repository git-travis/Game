#include "passive.h"


Passive::Passive(apType pType, std::string name, int damage, int heal, int speed, std::string filename):
	Item(PASSIVE, name, filename){
	_pType = pType;
	_damageAMT = damage;
	_healAMT = heal;
	_speedMOD = speed;
}
Passive::Passive():
	Item(PASSIVE, "EMPTY", "Sprites/BLANK.png"){
	_pType = HEAL;
}

Passive::~Passive(){

}

void Passive::updateDamage(int damage){
	_damageAMT = damage;
}
void Passive::updateHeal(int heal){
	_healAMT = heal;
}
void Passive::updateSpeed(int speed){
	_speedMOD = speed;
}

int Passive::getAddDmg(){
	return _damageAMT;
}
int Passive::getMultDmg(){
	return _multDmg;
}
int Passive::getHeal(){
	return _healAMT;
}
int Passive::getSpeed(){
	return _speedMOD;
}

void Passive::update(float elapsedTime, sf::Vector2f pos){
	//_sprite.setPosition(sf::Vector2f(pos.x + (size.x * 1.5) * -obj.x, pos.y + (size.y * 1.5) * -obj.y));
	setPos(pos);


}
