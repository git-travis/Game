#include "shooter.h"

Shooter::Shooter():
	Weapon(){

}

Shooter::~Shooter(){}

void Shooter::loadProjIMG(){
	if(this->getWType() == PROJECTILE){
		_projectile.loadIMG();
		_projectile.setScale(.5, .5);
	}
}

int Shooter::getAmmo(){
	return _ammo;
}
void Shooter::updateAmmo(int ammo){
	_ammo = ammo;
}

Projectile Shooter::getProjectile(float xmove, float ymove){
	_projectile.setMove(xmove, ymove);
	_projectile.setPos(sf::Vector2f(_sprite.getPosition().x + (xmove * 90), _sprite.getPosition().y + (ymove * 90)));
	return _projectile;
}
