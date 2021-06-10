#pragma once
#include "item.h"

class Shield: public Item{
public:
	Shield(std::string name, float total, std::string filename);
	Shield();
	~Shield();

	void loadTextures();
	void updateTexture();

	void activate(rectIMG* rect);

	float getTotal();
	float getRemaining();

	bool surviveHurt(float amount);
	//bool getRegen();

	void restore(float amt);

	inline sf::Vector2f getOffsetVector(float radians);

	void update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj, float rads);

private:
	std::vector<sf::Texture> _textures;
	bool _regenerating = false;
	float _timer = 0;
	float _total;
	float _remaining;

	sf::Vector2f _temp;

	enum dmgLvl{FULL, THREETHIRDS, TWOTHIRDS, ONETHIRD};
	dmgLvl _damage = FULL;
};
