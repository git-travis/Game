#pragma once
#include "item.h"

class Consumable: public Item{
public:
	Consumable(std::string name, std::string filename);
	Consumable();
	~Consumable();

	inline sf::Vector2f getOffsetVector(float radians);

	void update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads);

private:
	sf::Vector2f _temp;
};
