#pragma once
#include "menuState.h"

class Options: public MenuState{
public:
	Options(std::string textureName);
	~Options();

	void initText() override;
	menuStatus update(sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event) override;
private:
	menuStatus _back;
	int _counter = 0;
};
