#include "audio.h"

Audio::Audio(std::string textureName):
	MenuState(textureName){
	initImages();
}
Audio::~Audio(){

}

void Audio::initText(){
	sf::Text text;
	text.setFont(_font);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);

	text.setString("Music Volume +");
	_text.push_back(text);
	text.setString("Music Volume -");
	_text.push_back(text);
	text.setString("SFX Volume +");
	_text.push_back(text);
	text.setString("SFX Volume -");
	_text.push_back(text);
	text.setString("Back");
	_text.push_back(text);

	sf::FloatRect rect;
	for(unsigned int i = 0; i < _text.size(); i++){
		rect = _text[i].getLocalBounds();
		_text[i].setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
		//text.setPosition(menuSprites.at(i).getPosition().x, menuSprites.at(i).getPosition().y);
	}
}

menuStatus Audio::update(sf::Vector2f mousePos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event){
	if(_counter < 1){
		_back = prev;
		_counter++;
	}
	setPositions(*view);
	for(unsigned int i = 0; i < _sprites.size(); i++){
		window->draw(_sprites[i]);
		window->draw(_text[i]);
	}
	if(mouseClick){
		for(unsigned int i = 0; i < _sprites.size(); i++){
			//checks to see where the mouse was clicked in the menu
			if((game->checkXColl(_texture.getSize().x / 4, mousePos, _sprites.at(i).getPosition())) && (game->checkYColl(_texture.getSize().y / 4, mousePos, _sprites.at(i).getPosition()))){
				if(_text.at(i).getString() == "Music Volume +"){
					game->setVolume(game->getVolume() + 5);
					game->getMusic()->setVolume(game->getVolume());
				}
				if(_text.at(i).getString() == "Music Volume -"){
					game->setVolume(game->getVolume() - 5);
					game->getMusic()->setVolume(game->getVolume());
				}
				if(_text.at(i).getString() == "SFX Volume +"){
					game->setVolume(game->getVolume() + 5);
					game->getMusic()->setVolume(game->getVolume());
				}
				if(_text.at(i).getString() == "SFX Volume -"){
					game->setVolume(game->getVolume() - 5);
					game->getMusic()->setVolume(game->getVolume());
				}
				if(_text.at(i).getString() == "Back"){
					_counter = 0;
					return _back;
				}
			}
		}
	}
	return AUDIO;
}
