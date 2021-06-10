#include "health.h"
#include <cmath>

Health::Health(std::string name, int health, std::string filename):
	Item(ABILITY, name, filename){
	_health = health;
	loadTextures();
	updateTexture();
}
Health::Health():
	Item(HEALTH, "EMPTY", "Sprites/BLANK.png"){
	_health = 100;
	loadTextures();
	updateTexture();
}

Health::~Health(){

}
void Health::loadTextures(){
	sf::Texture temp;
	if(temp.loadFromFile("Sprites/Heart_High.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Heart_Mid.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Heart_Low.png")){
		_textures.push_back(temp);
	}
}

void Health::updateTexture(){
	if(_health >= 66){
		_sprite.setTexture(_textures[0]);
	}
	else if(_health >= 33){
		_sprite.setTexture(_textures[1]);
	}
	else{
		_sprite.setTexture(_textures[2]);
	}
}

void Health::updateHealth(float health){
	_health = health;
	updateTexture();

}

void Health::addHealth(float amount){
	_health += amount;
	updateTexture();
	if(_health > 100){
		_health = 100;
	}
}

void Health::loseHealth(float amount){
	_health -= amount;
	updateTexture();
}

float Health::getRemaining(){
	return _health;
}


void Health::update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj){
	_sprite.setPosition(sf::Vector2f(pos.x + (size.x * 1.5) * -obj.x, pos.y + (size.y * 1.5) * -obj.y));



}
