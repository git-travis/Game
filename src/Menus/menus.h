#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menuState.h"

#include "mainMenu.h"
#include "pauseMenu.h"
#include "options.h"
#include "graphics.h"
#include "audio.h"
#include "levelEditor.h"

class Menus{
public:
	Menus();
	virtual ~Menus();

	std::vector<sf::Sprite> getImages();
	void pause();

	void initMenus();
	//void update(sf::Event event);
	menuStatus update(float elapsedTime, sf::Vector2f pos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, sf::Event event);
private:
	float _mouseCooldown = 0.2;
	float _timer = 0;
	//std::vector<MenuState *> _menus;
	std::map<menuStatus, MenuState *> _menus;

	menuStatus _currentMenu = PAUSED;
	menuStatus _previousMenu = MAIN;
	MainMenu _main = MainMenu("Sprites/Menu_bar.png");
	PauseMenu _pause = PauseMenu("Sprites/Menu_bar.png");
	Options _options = Options("Sprites/Menu_bar.png");
	Graphics _graphics = Graphics("Sprites/Menu_bar.png");
	Audio _audio = Audio("Sprites/Menu_bar.png");
	Editor _editor = Editor("Sprites/Menu_bar.png");


};
