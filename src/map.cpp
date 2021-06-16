#include "map.h"
#include <sstream>
#include <fstream>
#include <iostream>

Map::Map(){

}
Map::~Map(){

}

void Map::save(std::string filename){
	if(_structures.size() < 1 && _spawners.size() < 1){
		std::cout << "Nothing to save!" << std::endl;
	}
	else{
		std::ofstream saveFile;
		//saving file as txt because thats all it is and to prevent potential issues with other programs
		saveFile.open("Maps/" + filename + ".txt", std::ios::app);

		for(unsigned i = 0; i < _structures.size(); i++){
			_tempCollidable = _structures.at(i);
			saveFile << _tempCollidable.getName() << "\n";
			saveFile << _tempCollidable.getFilename() << "\n";
			saveFile << _tempCollidable.getDestructible() << "\n";
			saveFile << _tempCollidable.getLinkable() << "\n";
			//getULCorner is the same as what getPos would be, SFML uses UL corner for positioning
			saveFile << _tempCollidable.getX() << "\n";
			saveFile << _tempCollidable.getY() << "\n";
			saveFile << _tempCollidable.getXSize() << "\n";
			saveFile << _tempCollidable.getYSize() << "\n";

			saveFile << "----\n";
		}
		saveFile << "Structures End\n";

		for(unsigned i = 0; i < _spawners.size(); i++){
			_tempSpawner = _spawners.at(i);
			saveFile << _tempSpawner.getPos().x << "\n";
			saveFile << _tempSpawner.getPos().y << "\n";
			saveFile << _tempSpawner.getCount() << "\n";
			saveFile << _tempSpawner.getTimer() << "\n";
			saveFile << _tempSpawner.getRandomSpawn() << "\n";

			saveFile << "----\n";
		}
		saveFile << "Spawners End\n";

		saveFile.close();
	}
	updateMapList(filename);
}

bool Map::load(std::string filename){
	bool structuresLoading = true;
	std::ifstream loadFile;
	std::string line;
	loadFile.open("Maps/" + filename + ".txt");

	if(loadFile.is_open()){
		//loop through the file to load all the structures for the map
		while(std::getline(loadFile, line) && structuresLoading){
			//using break to not messup the getline ordering
			if(line == "Structures End"){
				break;
			}
			//get the name and file name, make the object
			_tempCollidable = Collidable(line);
			std::getline(loadFile, line);
			_tempCollidable.setFileName(line);
			//check if destructible and linkable, set apporpriate tags (by default the tags are set to the inverse of whats shown here so we only need to update if they're different)
			std::getline(loadFile, line);
			if(line == "1"){
				_tempCollidable.setDestructible(true);
			}
			std::getline(loadFile, line);
			if(line == "0"){
				_tempCollidable.setLinkable(false);
			}
			//create variables, grab the information needed, and set it in the temp object
			int x, y, sizeX, sizeY;
			std::getline(loadFile, line);
			std::stringstream ssx(line);
			ssx >> x;
			std::getline(loadFile, line);
			std::stringstream ssy(line);
			ssy >> y;
			std::getline(loadFile, line);
			std::stringstream sssizeX(line);
			sssizeX >> sizeX;
			std::getline(loadFile, line);
			std::stringstream sssizeY(line);
			sssizeY >> sizeY;

			_tempCollidable.setPos(sf::Vector2f(x, y));
			_tempCollidable.setSizeX(sizeX);
			_tempCollidable.setSizeY(sizeY);

			//add the temp collidable
			_tempCollidable.build();
			this->addStructure(_tempCollidable);
			//ignore the last line
			std::getline(loadFile, line);
		}

		//structures done loading, now load spawners
		while(std::getline(loadFile, line)){
			if(line == "Spawners End"){
				break;
			}

			int x, y, count;
			float timer;

			std::stringstream ssx(line);
			ssx >> x;
			std::getline(loadFile, line);
			std::stringstream ssy(line);
			ssy >> y;
			std::getline(loadFile, line);
			std::stringstream sscount(line);
			sscount >> count;
			std::getline(loadFile, line);
			std::stringstream sstimer(line);
			sstimer >> timer;
			_tempSpawner = Spawner(Player(), count, timer);
			_tempSpawner.setPos(sf::Vector2f(x, y));

			//checks to see if randomSpawn is different from default
			std::getline(loadFile, line);
			if(line == "0"){
				_tempSpawner.setRandomSpawn();
			}
			_tempSpawner.loadImage();
			addSpawner(_tempSpawner);
			//ignore last line
			std::getline(loadFile, line);
		}
		return true;
	}
	else{
		std::cout << "Could not open file!" << std::endl;
		return false;
	}
	std::cout << "This should never fire!" << std::endl;
	return false;
}
void Map::updateMapList(std::string filename){
	bool added = false;
	std::ifstream loadFile;
	std::string line;
	loadFile.open("Maps/MapList.txt");

	if(loadFile.is_open()){
		//if the map list is too large this function can become an issue
		while(std::getline(loadFile, line)){
			//check if filename is already added
			if(line == filename){
				added = true;
			}
		}
		//if it is not added then add it
		if(!added){
			std::ofstream saveFile;
			saveFile.open("Maps/MapList.txt", std::ios::app);
			saveFile << filename << "\n";
			saveFile.close();
		}
	}
	else{
		std::cout << "Could not open map list file!" << std::endl;
	}
}

std::vector<std::string> Map::getMapList(){
	//read each line in MapList file for each map filename
	std::vector<std::string> list;
	std::ifstream loadFile;
	std::string line;
	loadFile.open("Maps/MapList.txt");

	if(loadFile.is_open()){
		while(std::getline(loadFile, line)){
			list.push_back(line);
		}
	}

	return list;
}

std::vector<Collidable> Map::getStructures(){
	return _structures;
}
std::vector<Spawner> Map::getSpawners(){
	return _spawners;
}
std::vector<sf::Sprite>* Map::getStructureSprites(){
	return &_structureSprites;
}
std::vector<sf::Sprite>* Map::getSpawnerSprites(){
	return &_spawnerSprites;
}

Collidable Map::getStructure(int pos){
	return _structures.at(pos);
}
Spawner Map::getSpawner(int pos){
	return _spawners.at(pos);
}

void Map::addStructure(Collidable structure){
	structure.build();
	_structures.push_back(structure);
	for(unsigned i = 0; i < structure.getSpritesX().size(); i++){
		_structureSprites.push_back(structure.getSpritesX()[i]);
	}
	for(unsigned i = 0; i < structure.getSpritesY().size(); i++){
		_structureSprites.push_back(structure.getSpritesY()[i]);
	}
}

void Map::addSpawner(Spawner spawner){
	_spawners.push_back(spawner);
	_spawnerSprites.push_back(*_spawners.at(_spawners.size() - 1).getSprite());
}

void Map::removeStructure(int pos){
	for(unsigned i = 0; i < _structureSprites.size(); i++){
		for(unsigned k = 0; k < _structures[pos].getSpritesX().size(); k++){
			if(_structureSprites[i].getPosition().x == _structures[pos].getSpritesX()[k].getPosition().x &&_structureSprites[i].getPosition().y == _structures[pos].getSpritesX()[k].getPosition().y){
				_structureSprites.erase(_structureSprites.begin() + i);
			}
		}
		for(unsigned k = 0; k < _structures[pos].getSpritesY().size(); k++){
			if(_structureSprites[i].getPosition().x == _structures[pos].getSpritesY()[k].getPosition().x && _structureSprites[i].getPosition().y == _structures[pos].getSpritesY()[k].getPosition().y){
				_structureSprites.erase(_structureSprites.begin() + i);
			}
		}
	}
	_structures.erase(_structures.begin() + pos);
}

void Map::removeSpawner(int pos){
	_spawners.erase(_spawners.begin() + pos);
	_spawnerSprites.erase(_spawnerSprites.begin() + pos);
}







