#include "menus.h"

Menus::Menus(){
	initMenus();
}
Menus::~Menus(){

}

void Menus::initMenus(){
	_menus.insert(std::make_pair(MAIN, &_main));
	_menus.insert(std::make_pair(PAUSED, &_pause));
	_menus.insert(std::make_pair(OPTIONS, &_options));
	_menus.insert(std::make_pair(GRAPHICS, &_graphics));
	_menus.insert(std::make_pair(AUDIO, &_audio));
	_menus.insert(std::make_pair(LEVELEDITOR, &_editor));
}

void Menus::pause(){
	_currentMenu = PAUSED;
}

std::vector<sf::Sprite> Menus::getImages(){
	return _menus.at(_currentMenu)->getImages();
}

menuStatus Menus::update(float elapsedTime, sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, sf::Event event){
	if(mouseClick && (_timer <= 0)){
		_previousMenu = _currentMenu;
		_currentMenu = _menus[_currentMenu]->update(pos, view, game, window, mouseClick, _previousMenu, event);
		_timer = _mouseCooldown;
	}
	else{
		if(_timer >= -1){
			_timer -= elapsedTime;
		}
		_currentMenu = _menus[_currentMenu]->update(pos, view, game, window, false, _previousMenu, event);
	}

	return _currentMenu;
}
