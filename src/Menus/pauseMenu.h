#pragma once
#include "menuState.h"

class PauseMenu: public MenuState{
public:
	PauseMenu(std::string textureName);
	~PauseMenu();

	void initText() override;
	menuStatus update(sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event) override;
private:

};
