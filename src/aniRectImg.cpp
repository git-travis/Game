#include "aniRectImg.h"

/*

aniRectIMG::aniRectIMG(int x, int y, int width, int height, std::string file, int frames):
		rectIMG(file){
	_frameIndex = 0;
	_maxFrames = frames;
	_currentAni = 0;
	_timeElapsed = 0;
	_visible = true;
	_notDone = true;
}

aniRectIMG::aniRectIMG(std::string file):
		rectIMG(file){
	_frameIndex = 0;
	_maxFrames = 0;
	_currentAni = 0;
	_timeElapsed = 0;
	_visible = true;
	_notDone = true;
}

aniRectIMG::~aniRectIMG(){}


void aniRectIMG::setupAni(){}

void aniRectIMG::playAni(int animation){
	_currentAni = animation;
	if(_visible){
		if(_frameIndex >= _animations.at(animation).size() - 1){
			_frameIndex = 0;
			_sprite.setTextureRect(_animations.at(animation).at(_frameIndex));
		}
		else{
			_frameIndex++;
			_sprite.setTextureRect(_animations.at(animation).at(_frameIndex));
		}
	}
}

void aniRectIMG::updateAni(int i){
	this->_currentAni = i;
}

void aniRectIMG::stopAni(){
	_frameIndex = 0;
	_notDone = false;
}

void aniRectIMG::addAni(int maxFrames, int x, int y, int width, int height){
	std::vector<sf::IntRect> _frames;
	//grabs sections of pixel animation map for each frame
	for(int i = 0; i < maxFrames; i ++){
		//Rectangle newRect = {(i + x) * width, y, width, height};
		_frames.push_back(sf::IntRect((i + x) * width, y, width, height));
	}
	_animations.push_back(_frames);
}


void aniRectIMG::update(){
	switch(_dirMove){
	case Direction::LEFT:
		this->updateDir(LEFT);
		break;
	case Direction::RIGHT:
		this->updateDir(RIGHT);
		updateAni(1);
		break;
	case Direction::UP:
		this->updateDir(UP);
		break;
	case Direction::DOWN:
		this->updateDir(DOWN);
		break;
	case Direction::STOPPED:
		updateAni(0);
		break;
	default:
		break;
	}
	playAni(_currentAni);

}

*/
