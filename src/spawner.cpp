#include "spawner.h"

#include <iostream>

Spawner::Spawner(Player entity, int count, float timer){
	_entity = entity;
	_count = count;
	_timer = timer;
	loadTextures();
}
Spawner::Spawner(int count, float timer){
	_randomSpawn = true;
	_count = count;
	_timer = timer;
	loadTextures();
}
Spawner::Spawner(){

}

Spawner::~Spawner(){}

sf::Sprite* Spawner::getSprite(){
	return &_sprite;
}

sf::Vector2f Spawner::getPos(){
	return _sprite.getPosition();
}

int Spawner::getCount(){
	return _count;
}
float Spawner::getTimer(){
	return _timer;
}
bool Spawner::getRandomSpawn(){
	return _randomSpawn;
}
Player Spawner::getEntity(){
	return _entity;
}

void Spawner::setEntity(Player entity){
	_entity = entity;
}

void Spawner::setCount(int count){
	_count = count;
}

void Spawner::setTimer(float timer){
	_timer = timer;
}

void Spawner::setPos(sf::Vector2f pos){
	_sprite.setPosition(pos);
}
void Spawner::setRandomSpawn(){
	//just sets it opposite of the current value
	//default is false
	_randomSpawn = !_randomSpawn;
}

void Spawner::loadImage(){
	//due to how SFML handles sprites/textures, this sort of obtuse way needs to be used instead of just changing the texture
	//This does allow for more creativity with the spawners though
	if(_count > 4){
		_sprite.setTexture(_textures[2]);
	}
	else if(_count > 2){
		_sprite.setTexture(_textures[1]);
	}
	else{
		_sprite.setTexture(_textures[0]);
	}
}

void Spawner::loadTextures(){
	sf::Texture temp;
	if(temp.loadFromFile("Sprites/Spawn_Easy.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Spawn_Medium.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Spawn_Hard.png")){
		_textures.push_back(temp);
	}
}

bool Spawner::checkColl(sf::Vector2f pos){
	return ((pos.x > _sprite.getPosition().x && pos.x < _sprite.getPosition().x + _textures[0].getSize().x) && (pos.y > _sprite.getPosition().y && pos.y < _sprite.getPosition().y + _textures[0].getSize().y));
}

void Spawner::update(float elapsedTime){

}
