#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "..\rectIMG.h"
#include "..\game.h"

class MenuState{
public:
	MenuState(std::string textureName);
	virtual ~MenuState();

	std::string _filename = "Sprites/BLANK.png";
	sf::Texture _texture;
	std::vector<sf::Sprite> _sprites;
	std::vector<sf::Text> _text;
	sf::Font _font;

	std::vector<sf::Sprite> getImages();
	std::vector<sf::Text> getText();

	virtual void initImages();
	virtual void initText();
	virtual void setPositions(sf::Vector2f viewPos);
	//void update(sf::Event event);
	virtual menuStatus update(sf::Vector2f pos, sf::Vector2f* viewPos, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event);

private:
};
