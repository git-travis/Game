#pragma once
#include "item.h"

class Health: public Item{
public:
	Health(std::string name, int health, std::string filename);
	Health();
	virtual ~Health();

	void loadTextures();
	void updateTexture();

	float getRemaining();

	void updateHealth(float health);
	void addHealth(float amount);
	void loseHealth(float amount);
	void gainHealth(float amount);

	void update(float elapsedTime, sf::Vector2f pos, sf::Vector2u size, sf::Vector2f obj);
private:
	float _health;
	std::vector<sf::Texture> _textures;
};
