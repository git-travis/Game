#pragma once
#include "menuState.h"

class MainMenu: public MenuState{
public:
	MainMenu(std::string name);
	~MainMenu();

	void initText() override;
	menuStatus update(sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event) override;
private:
};
