#pragma once

#include "player.h"

class Spawner{
public:
	Spawner(Player entity, int count, float timer);
	Spawner(int count, float timer);
	~Spawner();

	sf::Sprite* getSprite();
	sf::Vector2f getPos();
	Player getEntity();

	void setEntity(Player entity);
	void setCount(int count);
	void setTimer(float timer);
	void setPos(sf::Vector2f pos);
	void loadImage();
	void loadTextures();

	bool checkColl(sf::Vector2f);

	void update(float elapsedTime);

private:
	sf::Sprite _sprite;
	Player _entity;
	std::vector<sf::Texture> _textures;
	//sf::Texture _texture;

	bool _randomSpawn = false;
	int _count = 1;
	float _timer = 0;
};
