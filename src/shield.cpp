#include "shield.h"
#include <cmath>

Shield::Shield(std::string name, float total, std::string filename):
	Item(SHIELD, name, filename){
	_total = total;
	_remaining = total;
	loadTextures();
	updateTexture();
}
Shield::Shield():
	Item(SHIELD, "DOES NOT EXIST", "Sprites/BLANK.png"){
	_total = 0;
	_remaining = 0;
	loadTextures();
	updateTexture();
}
Shield::~Shield(){

}

void Shield::loadTextures(){
	sf::Texture temp;
	if(temp.loadFromFile("Sprites/Shield_High.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Shield_Mid.png")){
		_textures.push_back(temp);
	}
	if(temp.loadFromFile("Sprites/Shield_Low.png")){
		_textures.push_back(temp);
	}
}
void Shield::updateTexture(){
	if(_remaining >= 66){
		_sprite.setTexture(_textures[0]);
	}
	else if(_remaining >= 33){
		_sprite.setTexture(_textures[1]);
	}
	else{
		_sprite.setTexture(_textures[2]);
	}
}


float Shield::getTotal(){
	return _total;
}
float Shield::getRemaining(){
	return _remaining;
}

bool Shield::surviveHurt(float amount){
	_remaining -= amount;
	_regenerating = true;
	_timer = 0;

	updateTexture();

	if(_remaining <= 0){
		_remaining = 0;
		return false;
	}
	else if(_remaining >= 0){
		_damage = ONETHIRD;
	}
	else if(_remaining > 33 && _remaining < 66){
		_damage = TWOTHIRDS;
	}
	else{
		_damage = THREETHIRDS;
	}
	return true;
}
/*
bool Shield::getRegen(){
	return _regenerating;
}
*/
void Shield::restore(float amt){
	_remaining += amt;
	updateTexture();
}

inline sf::Vector2f Shield::getOffsetVector(float radians){
	radians += 1.178097; //67.5 degrees 0.3926991 for 22.5
	//radians = (radians * 180 / 3.14159265) + 35;
	//radians = radians * 3.14159265 / 180;
	return sf::Vector2f(cos(radians), sin(radians));
}


void Shield::update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads){
	_temp = getOffsetVector(rads);
	_sprite.setPosition(sf::Vector2f(pos.x + (size.x * 1.5) * -_temp.x, pos.y + (size.y * 1.5) * -_temp.y));


	if(_regenerating && _timer > 5){
		switch(_damage){
		case FULL:
			break;

		case THREETHIRDS:
			if(_remaining >= (.66 * _total) && _remaining < _total){
				_remaining += (10 * elapsedTime);
			}
			else{
				updateTexture();
				_regenerating = false;
				//_timer = 0;
			}
			break;

		case TWOTHIRDS:
			if(_remaining >= (.33 * _total) && _remaining < (.66 * _total)){
				_remaining += (10 * elapsedTime);
			}
			else{
				updateTexture();
				_regenerating = false;
				//_timer = 0;
			}
			break;

		case ONETHIRD:
			if(_remaining >= 0 && _remaining < (.33 * _total)){
				_remaining += (10 * elapsedTime);
			}
			else{
				updateTexture();
				_regenerating = false;
				//_timer = 0;
			}
			break;

		default:
			break;
		}
	}
	else if(_regenerating){
		_timer += elapsedTime;
	}




}







