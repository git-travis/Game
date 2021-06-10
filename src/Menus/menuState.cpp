#include "menuState.h"

MenuState::MenuState(std::string textureName){
	_filename = textureName;
	if (!_font.loadFromFile("Fonts/aAtmospheric.ttf")){
		std::cout << "FONT ATMOSPHERIC DID NOT LOAD" << std::endl;
	}
}
MenuState::~MenuState(){

}

void MenuState::initText(){
	sf::Text text;
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setString("BLANK");
	_text.push_back(text);
}
void MenuState::initImages(){
	initText();

    if(!_texture.loadFromFile(_filename)){
    	std::cout << "UNABLE TO OPEN MENU TEXTURE" << std::endl;
    }
    for(unsigned i = 0; i < _text.size(); i++){
    	//add sprites to the sprite vector relative to how many text entries there are and setup their positioning
    	_sprites.push_back(sf::Sprite(_texture));
    	_sprites[i].setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
    	_sprites[i].setTextureRect(sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y));
    	_sprites[i].setScale(0.5, 0.5);
    }

}

std::vector<sf::Sprite> MenuState::getImages(){
	return _sprites;
}
std::vector<sf::Text> MenuState::getText(){
	return _text;
}

void MenuState::setPositions(sf::Vector2f viewPos){
	for(unsigned i = 0; i < _sprites.size(); i++){
		//position the sprites relative to the view position
		_sprites[i].setPosition(viewPos.x, ((_texture.getSize().y * 1.1) * i) - 400 + viewPos.y);
	}
	for(unsigned i = 0; i < _text.size(); i++){
		//position the text entries relative to where the sprites are
		_text[i].setOrigin(_text[i].getLocalBounds().left + _text[i].getLocalBounds().width/2.0f, _text[i].getLocalBounds().top + _text[i].getLocalBounds().height/2.0f);
		_text[i].setPosition(_sprites[i].getPosition().x, _sprites[i].getPosition().y);
	}
}

menuStatus MenuState::update(sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event){
	setPositions(*view);
	std::cout << "update() is not overridden in a menu!" << std::endl;
	return PAUSED;
}
