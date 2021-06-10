#pragma once
#include "menuState.h"
#include "../map.h"

class Editor: public MenuState{
public:
	Editor(std::string textureName);
	~Editor();

	void inputText(sf::Event event);
	void loadFile();

	void drawSprites(sf::RenderWindow* window);

	void initText() override;
	void setPositions(sf::Vector2f viewPos) override;
	void moveCamera(sf::Vector2f* view, sf::Event event);

	//inline functions here just to help keep code clean
	inline void arrangeInputMenu(int i);
	inline void handleConfirm();
	inline menuStatus handleClicks(sf::Vector2f mousePos, Game* game, bool mouseClick, sf::Event event);


	menuStatus update(sf::Vector2f mousePos, sf::Vector2f* view, Game* game, sf::RenderWindow* window, bool mouseClick, menuStatus prev, sf::Event event) override;

private:
	enum confirmType{SPAWNER, SAVELEVEL, LOADLEVEL, NEWLEVEL, NEWCOLLIDABLE, BLANK};
	confirmType _confirm = BLANK;

	enum clickType{GUI, ADDCOLLIDABLE, ADDSPAWNER, DELETE, MOVE};
	clickType _click = GUI;

	std::string _textInput;
	std::string _input;

	Map _map = Map();
	Collidable _newCollidable = Collidable("Empty");
	Spawner _newSpawner = Spawner(0, 0);
	std::vector<sf::Sprite> _tempSprites;

	sf::Vector2f _inputPos;
	sf::Vector2f _confirmPos;
	sf::Vector2f _cancelPos;
	sf::Vector2f _mousePos1;
	sf::Vector2f _mousePos2;

	bool _backed = false;
	bool _loading = false;
	bool _options = false;

	int _clickCount = 0;
};
