#include "consumable.h"
#include <cmath>

Consumable::Consumable(std::string name, std::string filename):
	Item(SHIELD, name, filename){
}
Consumable::Consumable():
	Item(SHIELD, "DOES NOT EXIST", "Sprites/BLANK.png"){
}
Consumable::~Consumable(){

}

inline sf::Vector2f Consumable::getOffsetVector(float radians){
	radians += 5.1050881; //292.5 degrees
	//radians = (radians * 180 / 3.14159265) + 35;
	//radians = radians * 3.14159265 / 180;
	return sf::Vector2f(cos(radians), sin(radians));
}

void Consumable::update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads){
	_temp = getOffsetVector(rads);
	_sprite.setPosition(sf::Vector2f(pos.x + (size.x * 1.5) * -_temp.x, pos.y + (size.y * 1.5) * -_temp.y));




}
