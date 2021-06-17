#include "rectIMG.h"
#include <iostream>


rectIMG::rectIMG(std::string file):
	_file(file),
	_rect(0, 0, 0, 0),
	_dirMove(STOPPED){
	_amtMove = 1000;
	_move.x = 0;
	_move.y = 0;
	_maxMove = 10;
	_hbox = sf::Vector2f(1, 1);
	if(file != ""){
		loadIMG();
	}
}

rectIMG::rectIMG(sf::Texture texture, std::string file):
		_file(file),
		_rect(0, 0, 0, 0),
		_dirMove(STOPPED){
	_texture = texture;
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	_amtMove = 1000;
	_move.x = 0;
	_move.y = 0;
	_maxMove = 10;
	_hbox = sf::Vector2f(1, 1);
}

rectIMG::rectIMG(){}

rectIMG::~rectIMG(){}

const void rectIMG::loadIMG(){
	if(_texture.loadFromFile(_file)){
		_sprite.setTexture(_texture);
		_rect = sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y);
		_sprite.setTextureRect(_rect);
		_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	}
	else{
		printf("Could not load file! rectimg");
	}
}

const void rectIMG::loadIMG(std::string file){
	if(_texture.loadFromFile(file)){
		_sprite.setTexture(_texture);
		_file = file;
	}
	else{
		printf("Could not load file! rectimg");
	}
}

sf::Sprite* rectIMG::getSprite(){
	return &_sprite;
}

sf::Texture rectIMG::getText() const{
	return _texture;
}

std::string rectIMG::getFile() const{
	return _file;
}

sf::IntRect rectIMG::getRect() const{
	return _rect;
}


sf::Vector2u rectIMG::getSize(){
	return sf::Vector2u(this->_texture.getSize().x * _scaleX, this->_texture.getSize().y * _scaleY);
}



void rectIMG::changeAmtMove(int x){
	this->_amtMove = x;
}

void rectIMG::updateMove(sf::Vector2f move){
	_move = move;
}



void rectIMG::changePos(int x, int y){
	_sprite.setPosition(x, y);
}

void rectIMG::updateDir(Direction dir){
	this->_dirMove = dir;
	switch(dir){
	case UP:
		if(_move.y > -_maxMove){
			_move.y -= _amtMove;
		}
		break;
	case DOWN:
		if(_move.y < _maxMove){
			_move.y += _amtMove;
		}
		break;
	case LEFT:
		if(_move.x > -_maxMove){
			_move.x -= _amtMove;
		}
		break;
	case RIGHT:
		if(_move.x < _maxMove){
			_move.x += _amtMove;
		}
		break;
	case STOPPED:
		_move.x = 0;
		_move.y = 0;
		break;
	case STOPU:
		_move.y = 0;
		break;
	case STOPL:
		_move.x = 0;
		break;
	case STOPR:
		_move.x = 0;
		break;
	case STOPD:
		_move.y = 0;
		break;
	default:
		break;
	}
}

sf::Vector2f rectIMG::getPos(){
	return this->_sprite.getPosition();
}

void rectIMG::setPos(sf::Vector2f pos){
	_sprite.setPosition(pos);
}
void rectIMG::setRotation(float rot){
	_sprite.setRotation(rot);
}

void rectIMG::setRotating(float deg, float distance, float speed){
	_rotating = true;
	_deg = deg;
	_distance = distance;
	_rSpeed = speed;
}

void rectIMG::setScale(float x, float y){
	_sprite.setScale(x, y);
	_scaleX = x;
	_scaleY = y;
}

sf::Vector2f rectIMG::getAmountMoved(){
	return _amountMoved;
}

sf::Vector2f rectIMG::getSector(){
	return sf::Vector2f((int) (getPos().x / 125), (int) (getPos().y / 125));
}

void rectIMG::updateRect(float elapsedTime){
	_amountMoved = _move * elapsedTime;
	_sprite.move(_amountMoved);
}













