#include "projectile.h"
#include <iostream>

Projectile::Projectile(std::string name, float dmg, float speed, std::string filename):
	Item(MOVABLE, name, filename){
	_dmg = dmg;
	_speed = speed;
}

Projectile::Projectile():
		Item(ABILITY, "EMPTY", "Sprites/BLANK.png"){
	_dmg = 0;
	_speed = 0;
}

Projectile::~Projectile(){}

float Projectile::getDmg(){
	return _dmg;
}

void Projectile::setMove(float x, float y){
	_xy.x = x;
	_xy.y = y;
}

void Projectile::update(float elapsedTime){
	_sprite.move(_xy.x * _speed * elapsedTime, _xy.y * _speed * elapsedTime);
}
