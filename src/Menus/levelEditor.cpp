#include "levelEditor.h"
#include <sstream>
#include <cmath>

Editor::Editor(std::string textureName):
	MenuState(textureName){
	initImages();
}
Editor::~Editor(){

}

void Editor::drawSprites(sf::RenderWindow* window){
	for(unsigned i = 0; i < _tempSprites.size(); i++){
		window->draw(_tempSprites[i]);
	}
	for(unsigned i = 0; i < _map.getStructureSprites()->size(); i++){
		window->draw(_map.getStructureSprites()->at(i));
	}
	for(unsigned i = 0; i < _map.getSpawnerSprites()->size(); i++){
		window->draw(_map.getSpawnerSprites()->at(i));
	}
}

void Editor::inputText(sf::Event event){
	//add the latest key entry to buffer
	if(event.type == sf::Event::TextEntered){
		_input = event.text.unicode;
		_backed = false;
	}
	//add it to the string when a key is released
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::Backspace && !_backed){
			_textInput = _textInput.substr(0, _textInput.size() - 1);
			_text[_sprites.size() - 3].setString(_textInput);
			_backed = true;
		}
		//handle backspace
		else if(!_backed){
			_textInput += _input;
			_input.clear();
			_text[_sprites.size() - 3].setString(_textInput);
		}
	}
}

void Editor::initText(){
	sf::Text text;
	text.setFont(_font);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);

	text.setString("Back");
	_text.push_back(text);
	text.setString("Add Spawner");
	_text.push_back(text);
	text.setString("Save Level");
	_text.push_back(text);
	text.setString("New Level");
	_text.push_back(text);
	text.setString("Load Level");
	_text.push_back(text);
	text.setString("Add Collidable");
	_text.push_back(text);
	text.setString("Options");
	_text.push_back(text);

	//keeping these separate for orginization purposes
	text.setString("Delete"); //-5
	_text.push_back(text);
	text.setString("Move"); //-4
	_text.push_back(text);
	text.setString("_"); //-3
	_text.push_back(text);
	text.setString("Confirm"); //-2
	_text.push_back(text);
	text.setString("Cancel"); //-1
	_text.push_back(text);

	sf::FloatRect rect;
	for(unsigned i = 0; i < _text.size(); i++){
		rect = text.getLocalBounds();
		text.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
		//text.setPosition(menuSprites.at(i).getPosition().x, menuSprites.at(i).getPosition().y);
	}
}
void Editor::setPositions(sf::Vector2f viewPos){
	//not the best way to handle this, better to make a button object
	//doing this anyways because its a one off and easier
	_sprites[0].setPosition(viewPos.x - (1920 * .38), viewPos.y - (1080 * .45));
	_sprites[1].setPosition(viewPos.x + (1920 * .38), viewPos.y - (1080 * .45));
	_sprites[2].setPosition(viewPos.x + (1920 * .38), viewPos.y + (1080 * .45));
	_sprites[3].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x / 2, viewPos.y + (1080 * .45));
	_sprites[4].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x * 2 / 2, viewPos.y + (1080 * .45));
	_sprites[5].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x / 2, viewPos.y - (1080 * .45));
	_sprites[6].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x * 2 / 2, viewPos.y - (1080 * .45));

	//options menu
	_sprites[_sprites.size() - 5].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x * 2 / 2, (-(1080 * .45) + _texture.getSize().y / 2));
	_sprites[_sprites.size() - 4].setPosition(viewPos.x + (1920 * .38) - _texture.getSize().x * 2 / 2, (-(1080 * .45) + _texture.getSize().y * 2 / 2));

	//text input menu
	_sprites[_sprites.size() - 3].setPosition(viewPos.x + _inputPos.x, viewPos.y + _inputPos.y);
	_sprites[_sprites.size() - 2].setPosition(viewPos.x + _confirmPos.x, viewPos.y + _confirmPos.y);
	_sprites[_sprites.size() - 1].setPosition(viewPos.x + _cancelPos.x, viewPos.y + _cancelPos.y);

	//_sprites[_sprites.size() - 3].setPosition(viewPos.x + (1920 * .38), viewPos.y - (1080 * .45) + _texture.getSize().y / 2);
	//_sprites[_sprites.size() - 2].setPosition(viewPos.x + (1920 * .38), viewPos.y - (1080 * .45) + _texture.getSize().y * 2 / 2);
	//_sprites[_sprites.size() - 1].setPosition(viewPos.x + (1920 * .38), viewPos.y - (1080 * .45) + _texture.getSize().y * 3 / 2);


	for(unsigned i = 0; i < _text.size(); i++){
		//position the text entries relative to where the sprites are
		_text[i].setOrigin(_text[i].getLocalBounds().left + _text[i].getLocalBounds().width/2.0f, _text[i].getLocalBounds().top + _text[i].getLocalBounds().height/2.0f);
		_text[i].setPosition(_sprites[i].getPosition().x, _sprites[i].getPosition().y);
	}
}

void Editor::moveCamera(sf::Vector2f* view, sf::Event event){
	//simple camera movement implementation
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		view->y--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		view->y++;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		view->x--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		view->x++;
	}
}

void Editor::arrangeInputMenu(int i){
	_textInput.clear();
	_text[_sprites.size() - 3].setString("_");
	switch(i){
	case 0: //Load Level
		_inputPos.x = ((1920 * .38) - _texture.getSize().x * 2 / 2);
		_inputPos.y = ((1080 * .45) - _texture.getSize().y / 2);
		_confirmPos.x = ((1920 * .38) - _texture.getSize().x * 2 / 2);
		_confirmPos.y = ((1080 * .45) - _texture.getSize().y * 2 / 2);
		_cancelPos.x = ((1920 * .38) - _texture.getSize().x * 2 / 2);
		_cancelPos.y = ((1080 * .45) - _texture.getSize().y * 3 / 2);
		break;
	case 1: //Save Level
		_inputPos.x = (1920 * .38);
		_inputPos.y = ((1080 * .45) - _texture.getSize().y / 2);
		_confirmPos.x = (1920 * .38);
		_confirmPos.y = ((1080 * .45) - _texture.getSize().y * 2 / 2);
		_cancelPos.x = (1920 * .38);
		_cancelPos.y = ((1080 * .45) - _texture.getSize().y * 3 / 2);
		break;
	case 2: //Add Spawner
		_inputPos.x = (1920 * .38);
		_inputPos.y = (-(1080 * .45) + _texture.getSize().y / 2);
		_confirmPos.x = (1920 * .38);
		_confirmPos.y = (-(1080 * .45) + _texture.getSize().y * 2 / 2);
		_cancelPos.x = (1920 * .38);
		_cancelPos.y = (-(1080 * .45) + _texture.getSize().y * 3 / 2);
		break;
	case 3: //New Level
		_inputPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_inputPos.y = ((1080 * .45) - _texture.getSize().y / 2);
		_confirmPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_confirmPos.y = ((1080 * .45) - _texture.getSize().y * 2 / 2);
		_cancelPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_cancelPos.y = ((1080 * .45) - _texture.getSize().y * 3 / 2);
		break;
	case 4: //New Collidable
		_inputPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_inputPos.y = -((1080 * .45) - _texture.getSize().y / 2);
		_confirmPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_confirmPos.y = -((1080 * .45) - _texture.getSize().y * 2 / 2);
		_cancelPos.x = ((1920 * .38) - _texture.getSize().x / 2);
		_cancelPos.y = -((1080 * .45) - _texture.getSize().y * 3 / 2);
		break;
	}
}

void Editor::handleConfirm(){
	switch(_confirm){
	case SPAWNER:
		if(_textInput.find(",") != std::string::npos){
			std::stringstream temp;
			temp << _textInput.substr(0, _textInput.find(",", 0));
			int x, y;
			temp >> x;
			temp.clear();
			temp << _textInput.substr(_textInput.find(",") + 2, _textInput.size());
			temp >> y;
			_newSpawner = Spawner(x, y);
			_newSpawner.loadImage();
			_loading = false;
			_click = ADDSPAWNER;
		}
		else{
			std::cout << "Incorrect Input" << std::endl;
		}
		break;

	case SAVELEVEL:
		break;

	case LOADLEVEL:
		break;

	case NEWLEVEL:
		break;

	case NEWCOLLIDABLE:
		if(_textInput.find(",") != std::string::npos){
			_newCollidable = Collidable("New Collidable");
			std::stringstream temp;
			temp << _textInput.substr(0, _textInput.find(",", 0));
			int x, y;
			temp >> x;
			temp.clear();
			temp << _textInput.substr(_textInput.find(",") + 2, _textInput.size());
			temp >> y;
			_newCollidable.setSizeX(x);
			_newCollidable.setSizeY(y);
			_loading = false;
			_click = ADDCOLLIDABLE;
		}
		else{
			std::cout << "Incorrect Input" << std::endl;
		}

		break;

	default:
		break;
	}
}

menuStatus Editor::handleClicks(sf::Vector2f mousePos, Game* game, bool mouseClick, sf::Event event){
	switch(_click){
		case GUI:
			if(event.type == sf::Event::MouseButtonReleased){
				for(unsigned int i = 0; i < _sprites.size(); i++){
						//checks to see where the mouse was clicked in the menu
						if((game->checkXColl(_texture.getSize().x / 4, mousePos, _sprites.at(i).getPosition())) && (game->checkYColl(_texture.getSize().y / 4, mousePos, _sprites.at(i).getPosition()))){
							//can't use a switch with strings :(
							if(_text.at(i).getString() == "Back"){
								return MAIN;
							}
							if(_text.at(i).getString() == "Cancel" && _loading){
								_textInput.clear();
								_text[_sprites.size() - 3].setString("_");
								_loading = false;
							}
							if(_text.at(i).getString() == "Load Level"){
								arrangeInputMenu(0);
								_loading = true;
								_confirm = LOADLEVEL;
							}
							if(_text.at(i).getString() == "Save Level"){
								arrangeInputMenu(1);
								_loading = true;
								_confirm = SAVELEVEL;
							}
							if(_text.at(i).getString() == "New Level"){
								arrangeInputMenu(3);
								_loading = true;
								_confirm = NEWLEVEL;
							}
							if(_text.at(i).getString() == "Add Spawner"){
								arrangeInputMenu(2);
								_loading = true;
								_confirm = SPAWNER;
							}
							if(_text.at(i).getString() == "Add Collidable"){
								arrangeInputMenu(4);
								_loading = true;
								_confirm = NEWCOLLIDABLE;
							}
							if(_text.at(i).getString() == "Options"){
								_options = true;
							}
							if(_text.at(i).getString() == "Delete"){
								_click = DELETE;
								_options = false;
							}
							if(_text.at(i).getString() == "Move"){
								_click = MOVE;
								_options = false;
							}
							if(_text.at(i).getString() == "Confirm" && _loading){
								handleConfirm();
							}
						}
					}
			}
			break;

		case ADDCOLLIDABLE:
			_tempSprites.clear();
			//set position relative to a grid of size 150
			//ceil() keeps there from being a deadzone in the middle and the -150 keeps it centered on the cursor
			_newCollidable.setPos(sf::Vector2f((std::ceil(mousePos.x / 150) * 150) - 150, (std::ceil(mousePos.y / 150) * 150) - 150));
			_newCollidable.build();
			for(unsigned i = 0; i < _newCollidable.getSpritesX().size(); i++){
				_tempSprites.push_back(_newCollidable.getSpritesX()[i]);
			}
			for(unsigned i = 0; i < _newCollidable.getSpritesY().size(); i++){
				_tempSprites.push_back(_newCollidable.getSpritesY()[i]);
			}
			if(mouseClick){
				_tempSprites.clear();
				_map.addStructure(_newCollidable);
				_click = GUI;
			}

			/*
			//code for potential two mouse click size definition of structure size, will revisit later
			if(_addCollidable == 1){
				_mousePos1 = mousePos;
				_addCollidable = 2;
			}
			else if(_addCollidable == 2){
				_mousePos2 = mousePos;
				_addCollidable = 0;
				//_newCollidable = Collidable("New Collidable");
				_newCollidable.setPos(_mousePos1);
				//_newCollidable.setSizeX(abs(_mousePos1.x - _mousePos2.x) / _newCollidable.getSprite().getTexture()->getSize().x);
				//_newCollidable.setSizeY(abs(_mousePos1.y - _mousePos2.y) / _newCollidable.getSprite().getTexture()->getSize().y);
				_newCollidable.build();
			}
				*/

			break;

		case ADDSPAWNER:
			_tempSprites.clear();
			//set position relative to a grid of size 150
			//ceil() keeps there from being a deadzone in the middle and the -150 keeps it centered on the cursor
			_newSpawner.setPos(sf::Vector2f((std::ceil(mousePos.x / 150) * 150) - 150, (std::ceil(mousePos.y / 150) * 150) - 150));
			_tempSprites.push_back(*_newSpawner.getSprite());
			if(mouseClick){
				_tempSprites.clear();
				_map.addSpawner(_newSpawner);
				_click = GUI;
			}
			break;

		case DELETE:
			if(mouseClick){
				_click = GUI;
				for(unsigned i = 0; i < _map.getStructures().size(); i++){
					if(_map.getStructures()[i].checkColl(mousePos)){
						_map.removeStructure(i);
					}
				}
				for(unsigned i = 0; i < _map.getSpawners().size(); i++){
					if(_map.getSpawners()[i].checkColl(mousePos)){
						_map.removeSpawner(i);
					}
				}
			}
			break;

		case MOVE:
			if(mouseClick){
				_click = GUI; //this makes a click always reset to prevent getting stuck
				for(unsigned i = 0; i < _map.getStructures().size(); i++){
					if(_map.getStructures()[i].checkColl(mousePos)){
						_newCollidable = _map.getStructure(i);
						_map.removeStructure(i);
						_click = ADDCOLLIDABLE; //just reuse the add code, no need to reimplement a feature
					}
				}
				for(unsigned i = 0; i < _map.getSpawners().size(); i++){
					if(_map.getSpawners()[i].checkColl(mousePos)){
						_newSpawner = _map.getSpawner(i);
						_map.removeSpawner(i);
						_click = ADDSPAWNER; //just reuse the add code, no need to reimplement a feature
					}
				}
			}
			break;

		default:
			break;
		}
	return LEVELEDITOR;
}

menuStatus Editor::update(sf::Vector2f mousePos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event){
	setPositions(*view);
	drawSprites(window);
	moveCamera(view, event);


	for(unsigned i = 0; i < _sprites.size() - 5; i++){
		window->draw(_sprites[i]);
		window->draw(_text[i]);
	}
	if(_loading){
		inputText(event);
		window->draw(_sprites[_sprites.size() - 3]);
		window->draw(_text[_sprites.size() - 3]);
		window->draw(_sprites[_sprites.size() - 2]);
		window->draw(_text[_sprites.size() - 2]);
		window->draw(_sprites[_sprites.size() - 1]);
		window->draw(_text[_sprites.size() - 1]);
	}
	if(_options){
		window->draw(_sprites[_sprites.size() - 4]);
		window->draw(_text[_sprites.size() - 4]);
		window->draw(_sprites[_sprites.size() - 5]);
		window->draw(_text[_sprites.size() - 5]);
	}



	return handleClicks(mousePos, game, mouseClick, event);
}
