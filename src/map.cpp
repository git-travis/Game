#include "map.h"
#include <sstream>

Map::Map(){

}
Map::~Map(){

}

void Map::save(std::string filename){
	std::ofstream saveFile;
	//opens the maps file
	saveFile.open(filename, std::ios_base::app);
	Collidable temp;

	for(unsigned i = 0; i < _structures.size(); i++){
		temp = _structures.at(i);
		saveFile << temp.getName() + "\n";
		saveFile << temp.getFilename() + "\n";
		saveFile << temp.getDestructible() + "\n";
		saveFile << temp.getLinkable() + "\n";
		//getULCorner is the same as what getPos would be, SFML uses UL corner for positioning
		saveFile << temp.getX() + "\n";
		saveFile << temp.getY() + "\n";
		saveFile << temp.getXSize() + "\n";
		saveFile << temp.getYSize() + "\n";
		saveFile << "----\n";
	}


	saveFile.close();
}

bool Map::load(std::string filename){
	bool success = true;
	std::ifstream loadFile;
	std::string line;
	Collidable temp;
	loadFile.open(filename);

	if(loadFile.is_open()){
		//loop through the file to load all the parameters for the map
		while(std::getline(loadFile, line)){
			//get the name and file name, make the object
			temp = Collidable(line);
			std::getline(loadFile, line);
			temp.setFileName(line);
			//check if destructible and linkable, set apporpriate tags (by default the tags are set to the inverse of whats shown here so we only need to update if they're different)
			std::getline(loadFile, line);
			if(line == "true"){
				temp.setDestructible(true);
			}
			std::getline(loadFile, line);
			if(line == "false"){
				temp.setLinkable(false);
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

			temp.setPos(sf::Vector2f(x, y));
			temp.setSizeX(sizeX);
			temp.setSizeY(sizeY);

			//add the temp object to the array
			_structures.push_back(temp);
			//ignore the last line
			std::getline(loadFile, line);
		}
		return success;
	}
	else{
		return false;
	}
	return false;
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







