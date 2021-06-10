#include "pauseMenu.h"

PauseMenu::PauseMenu(std::string textureName):
	MenuState(textureName){
	initImages();
}
PauseMenu::~PauseMenu(){

}

void PauseMenu::initText(){
	sf::Text text;
	text.setFont(_font);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);

	text.setString("Resume");
	_text.push_back(text);
	text.setString("Options");
	_text.push_back(text);
	text.setString("Main Menu");
	_text.push_back(text);
	text.setString("Quit");
	_text.push_back(text);

	sf::FloatRect rect;
	for(unsigned i = 0; i < _text.size(); i++){
		rect = _text[i].getLocalBounds();
		_text[i].setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
		//text.setPosition(menuSprites.at(i).getPosition().x, menuSprites.at(i).getPosition().y);
	}
}

menuStatus PauseMenu::update(sf::Vector2f mousePos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event){
	setPositions(*view);
	for(unsigned i = 0; i < _sprites.size(); i++){
		window->draw(_sprites[i]);
		window->draw(_text[i]);
	}
	if(mouseClick){
		for(unsigned i = 0; i < _sprites.size(); i++){
			//checks to see where the mouse was clicked in the menu
			if((game->checkXColl(_texture.getSize().x / 4, mousePos, _sprites.at(i).getPosition())) && (game->checkYColl(_texture.getSize().y / 4, mousePos, _sprites.at(i).getPosition()))){
				if(_text.at(i).getString() == "Resume"){
					game->setPaused(false);
					window->setMouseCursorVisible(false);
					return UNPAUSED;
				}
				if(_text.at(i).getString() == "Options"){
					return OPTIONS;
				}
				if(_text.at(i).getString() == "Main Menu"){
					return MAIN;
				}
				if(_text.at(i).getString() == "Quit"){
					window->close();
				}
			}
		}
	}
	return PAUSED;
}
