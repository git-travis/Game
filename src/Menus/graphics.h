#pragma once
#include "menuState.h"

class Graphics: public MenuState{
public:
	Graphics(std::string textureName);
	~Graphics();

	void initText() override;
	menuStatus update(sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event) override;
private:
	menuStatus _back = OPTIONS;
	int _counter = 0;
};
