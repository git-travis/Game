#include "item.h"

Item::Item(itemType type, std::string name, std::string filename, std::string pickupName, std::string useName):
	rectIMG(filename){
	_type = type;
	_name = name;
	_sound = true;
	_pickupName = pickupName;
	_useName = useName;
}
Item::Item(itemType type, std::string name, std::string filename):
	rectIMG(filename){
	_type = type;
	_name = name;
}

Item::Item(){
	_type = PASSIVE;
	_name = "DOES NOT EXIST";
}

Item::~Item(){

}

std::string Item::getName(){
	return _name;
}

void Item::update(float elapsedTime){
	this->updateRect(elapsedTime);
}

itemType Item::getType(){
	return _type;
}

void Item::updateDesc(std::string desc){
	_desc = desc;
}


std::string Item::getPickup(){
	return _pickupName;
}
std::string Item::getUse(){
	return _useName;
}
