#pragma once
#include <string>
#include "globals.h"
#include "rectIMG.h"

class Item: public rectIMG{
public:
	Item(itemType type, std::string name, std::string filename, std::string pickupName, std::string useName);
	Item(itemType type, std::string name, std::string filename);
	Item();
	~Item();
	std::string getName();
	void update(float elapsedTime);
	itemType getType();
	void updateDesc(std::string desc);
	std::string getPickup();
	std::string getUse();

private:
	bool _sound = false;
	itemType _type;
	std::string _name;
	std::string _pickupName = "Audio/filler.ogg";
	std::string _useName = "Audio/filler.ogg";


	std::string _desc = "EMPTY";

};
