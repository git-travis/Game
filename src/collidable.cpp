#include "collidable.h"
#include <iostream>

Collidable::Collidable(std::string name){
	_name = name;
	_filename = "Sprites/Wall_Link.png";
	if(_texture.loadFromFile(_filename)){
		_pos = sf::Vector2f(0, 0);
		_sizeX = 0;
		_sizeY = 0;
	}
	else{
		std::cout << "Could not load file: collidable:: " << _filename << std::endl;
	}
}
Collidable::Collidable(std::string name, sf::Vector2f startCorner, sf::Vector2f endCorner){
	_name = name;
	_filename = "Sprites/Wall_Link.png";
	if(_texture.loadFromFile(_filename)){
		_pos = sf::Vector2f(0, 0);
		_sizeX = 0;
		_sizeY = 0;
	}
	else{
		std::cout << "Could not load file: collidable:: " << _filename << std::endl;
	}
}
Collidable::Collidable(std::string name, std::string filename, int xpos, int ypos, int xsize, int ysize){
	_name = name;
	_filename = filename;
	if(_texture.loadFromFile(filename)){
		_pos = sf::Vector2f(xpos, ypos);
		_sizeX = xsize;
		_sizeY = ysize;
	}
	else{
		std::cout << "Could not load file: collidable:: " << _filename << std::endl;
	}
	_centralPos = sf::Vector2f((_pos.x + ((_texture.getSize().x * _sizeX) / 2)), (_pos.y + ((_texture.getSize().x * _sizeY) / 2)));
}

Collidable::Collidable(std::string name, std::string filename, int xpos, int ypos, bool dest){
	_linkable = false;
	/*
	_sprite = rectIMG(filename);
	_sprite.setPos(sf::Vector2f(xpos, ypos));
	_pos = _sprite.getPos();
	*/
	if(_texture.loadFromFile(filename)){
		_pos = sf::Vector2f(xpos, ypos);
	}
	else{
		std::cout << "Could not load file: collidable:: " << _filename << std::endl;
	}
	_destructible = dest;
}

Collidable::Collidable(){}

Collidable::~Collidable(){}


void Collidable::build(){
	if(_built){
		for(int i = 0; i < _sizeX; i++){
			_linksX[i].setPosition(_pos.x + (_texture.getSize().x * i) - (_texture.getSize().y / 2) + _texture.getSize().y / 2, _pos.y - _texture.getSize().y / 2);
			_linksX[i + _sizeX].setPosition(_pos.x + (_texture.getSize().x * i) - (_texture.getSize().y / 2) + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * _sizeY) - _texture.getSize().y / 2);
		}
		for(int i = 0; i < _sizeY; i++){
			_linksY[i].setPosition(_pos.x + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * i) + (_texture.getSize().y / 2) - _texture.getSize().y / 2);
			_linksY[i + _sizeY].setPosition(_pos.x + (_texture.getSize().x * _sizeX) + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * i) + (_texture.getSize().y / 2) - _texture.getSize().y / 2);
		}
	}
	else{
		for(int i = 0; i < _sizeX; i++){
			_linksX.push_back(sf::Sprite(_texture));
			_linksX[i].setPosition(_pos.x + (_texture.getSize().x * i) - (_texture.getSize().y / 2) + _texture.getSize().y / 2, _pos.y - _texture.getSize().y / 2);
		}
		for(int i = _sizeX; i < _sizeX + _sizeX; i++){
			_linksX.push_back(sf::Sprite(_texture));
			_linksX[i + _sizeX].setPosition(_pos.x + (_texture.getSize().x * i) - (_texture.getSize().y / 2) + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * _sizeY) - _texture.getSize().y / 2);
		}
		for(int i = 0; i < _sizeY; i++){
			_linksY.push_back(sf::Sprite(_texture));
			_linksY[i].setRotation(90);
			_linksY[i].setPosition(_pos.x + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * i) + (_texture.getSize().y / 2) - _texture.getSize().y / 2);
		}
		for(int i = _sizeY; i < _sizeY + _sizeY; i++){
			_linksY.push_back(sf::Sprite(_texture));
			_linksY[i].setRotation(90);
			_linksY[i + _sizeY].setPosition(_pos.x + (_texture.getSize().x * _sizeX) + _texture.getSize().y / 2, _pos.y + (_texture.getSize().x * i) + (_texture.getSize().y / 2) - _texture.getSize().y / 2);
		}
		_built = true;
	}
}


void Collidable::setDestructible(bool dest){
	_destructible = dest;
}
void Collidable::setLinkable(bool linkable){
	_linkable = linkable;
}
void Collidable::destroy(){

}
void Collidable::setFileName(std::string filename){
	_filename = filename;
	if(_texture.loadFromFile(_filename)){
		_pos = sf::Vector2f(0, 0);
		_sizeX = 0;
		_sizeY = 0;
	}
}

int Collidable::getDropPos(){
	return _dropPos;
}
void Collidable::setDropPos(int pos){
	_dropPos = pos;
}



void Collidable::setSizeX(int size){
	_sizeX = size;
}
void Collidable::setSizeY(int size){
	_sizeY = size;
}
void Collidable::setPos(sf::Vector2f pos){
	_pos = pos;
}

std::vector<sf::Sprite> Collidable::getSpritesX(){
	return _linksX;
}
std::vector<sf::Sprite> Collidable::getSpritesY(){
	return _linksY;
}
sf::Sprite Collidable::getSprite(){
	sf::Sprite sp = sf::Sprite(_texture);
	sp.setPosition(_pos);
	return sp;
}

sf::Vector2f Collidable::getULCorner(){
	return _pos;
}
sf::Vector2f Collidable::getCentralPos(){
	return _centralPos;
}
float Collidable::getXLines(){
	return (_sizeX * _texture.getSize().x);
}
float Collidable::getYLines(){
	return (_sizeY * _texture.getSize().x);
}

std::string Collidable::getName(){
	return _name;
}
std::string Collidable::getFilename(){
	return _filename;
}
int Collidable::getXSize(){
	return _sizeX;
}
int Collidable::getYSize(){
	return _sizeY;
}
int Collidable::getX(){
	return _pos.x;
}
int Collidable::getY(){
	return _pos.y;
}
sf::Vector2f Collidable::getSector(){
	return sf::Vector2f((int) (_pos.x / 125), (int) (_pos.y / 125));
}

bool Collidable::getDestructible(){
	return _destructible;
}
bool Collidable::getLinkable(){
	return _linkable;
}

bool Collidable::checkColl(sf::Vector2f pos){
	return ((pos.x > getULCorner().x && pos.x < getULCorner().x + getXLines()) && (pos.y > getULCorner().y && pos.y < getULCorner().y + getYLines()));
}

void Collidable::update(float elapsedTime){

}
