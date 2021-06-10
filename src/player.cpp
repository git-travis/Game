#include "player.h"

#include <iostream>

Player::Player(std::string name, std::string filename):
	rectIMG(filename){
	_name = name;
	_shield->loadIMG();
	_health->loadIMG();
	_shield->setScale(0.4, 0.4);
	_health->setScale(0.4, 0.4);
}
Player::Player():
	rectIMG(""){
	_name = "nothing";
	_shield->loadIMG();
	_health->loadIMG();
	_shield->setScale(0.4, 0.4);
	_health->setScale(0.4, 0.4);
}
Player::~Player(){

}

void Player::setAbility(Ability* ability){
	_ability = ability;
}
void Player::setPassive(Passive* passive){
	_passive = passive;
}
void Player::setShield(Shield* shield){
	_shield = shield;
}
void Player::setWeapon(Weapon* weapon){
	_weapon = weapon;
}
void Player::setHealth(Health* health){
	_health = health;
}
void Player::setConsumable(Consumable* consumable){
	_consumable = consumable;
}
Weapon Player::getWeapon(){
	return *_weapon;
}
Passive Player::getPassive(){
	return *_passive;
}
Ability Player::getAbility(){
	return *_ability;
}
Shield Player::getShield(){
	return *_shield;
}
Health Player::getHealth(){
	return *_health;
}
Consumable Player::getConsumable(){
	return *_consumable;
}
Projectile Player::getProjectile(sf::Vector2f move){
	return _weapon->getProjectile(move.x, move.y);
}

Item Player::getDrop(itemType type){
	switch(type){
	case ABILITY:
		return *_ability;
		break;
	case PASSIVE:
		return *_passive;
		break;
	case SHIELD:
		return *_shield;
		break;
	case WEAPON:
		return *_weapon;
		break;
	case HEALTH:
		return *_health;
		break;
	default:
		return Item();
		break;
	}
}




void Player::attack(){
	_weapon->setAttacking();
}
void Player::triggerAbility(){
	if(_ability->offCooldown()){
		switch(_ability->getAType()){
		case HEAL:
			_health->addHealth(_ability->getHeal());
			break;
		case DAMAGE:
			break;
		case MOVEMENT:
			if(_ability->getAMType() == TELEPORT){
				if(_ability->getAmtUsed() == 0){
					_ability->setTelePos(getPos());
					_ability->setAmtUsed(1);
					_spawnables.push_back(_ability->getSpawnable());
					_spawnables[0].setPosition(getPos());
				}
				else{
					setPos(_ability->getTelePos());
					_ability->setAmtUsed(0);
					_spawnables.erase(_spawnables.begin());
				}

			}
			else{
				changeAmtMove(_ability->getSpeed());
			}

			break;
		default:
			break;
		}
		_ability->coolDown();
	}
}


sf::Sprite Player::getAbilitySprite(){
	return _ability->getSprite();
}
sf::Sprite Player::getPassiveSprite(){
	return _passive->getSprite();
}
sf::Sprite Player::getShieldSprite(){
	return _shield->getSprite();
}
sf::Sprite Player::getWeaponSprite(){
	return _weapon->getSprite();
}
sf::Sprite Player::getHealthSprite(){
	return _health->getSprite();
}
sf::Sprite Player::getConsumableSprite(){
	return _consumable->getSprite();
}

void Player::move(sf::Vector2f move, float elapsedTime){
	move *= (elapsedTime);
	_sprite.move(move);
}

bool Player::isAlive(){
	return _alive;
}

void Player::die(){

}
float Player::hurt(float amount){
	if(_shield->surviveHurt(amount) && _shield->getRemaining() > 0){
		_health->loseHealth(amount * 0.25);
	}
	else{
		_health->loseHealth(amount);
	}
	if(_health->getRemaining() <= 0){
		_alive = false;
	}
	return _health->getRemaining();
}


std::vector<sf::Sprite> Player::getSpawnables(){
	return _spawnables;
}
bool Player::getAttacking(){
	return _weapon->getAttacking();
}


void Player::update(float elapsedTime, sf::Vector2f mouse, sf::Vector2f obj, float rad, float mouseAngle){
	this->updateRect(elapsedTime);
	_health->update(elapsedTime, getPos(), getSize(), mouse);
	_ability->update(elapsedTime, _health->getPos());
	_shield->update(elapsedTime, getPos(), getSize(), mouse, rad);
	_passive->update(elapsedTime, _shield->getPos());
	_weapon->update(elapsedTime, getPos(), getSize(), obj, rad, mouseAngle);
	_consumable->update(elapsedTime, getPos(), getSize(), mouse, rad);
}


