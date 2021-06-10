#pragma once

#include "collidable.h"
#include "spawner.h"
#include <fstream>

class Map{
public:
	Map();
	~Map();

	void save(std::string filename);
	bool load(std::string filename);

	//use this to load/initialize collidables into the game
	std::vector<Collidable> getStructures();
	std::vector<Spawner> getSpawners();
	std::vector<sf::Sprite>* getStructureSprites();
	std::vector<sf::Sprite>* getSpawnerSprites();

	Collidable getStructure(int pos);
	Spawner getSpawner(int pos);

	void addStructure(Collidable structure);
	void addSpawner(Spawner spawner);
	void removeStructure(int pos);
	void removeSpawner(int pos);

private:
	std::vector<Collidable> _structures;
	std::vector<sf::Sprite> _structureSprites;
	std::vector<sf::Sprite> _spawnerSprites;
	std::vector<Spawner> _spawners;

	sf::Vector2f _playerSpawn;
};
