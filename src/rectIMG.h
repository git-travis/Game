#pragma once
#include "globals.h"

#include <SFML/Graphics.hpp>
#include <string>

class rectIMG{
public:
	rectIMG(std::string file);
	rectIMG(sf::Texture texture, std::string file);
	rectIMG();
	virtual ~rectIMG();

	const void loadIMG(std::string file);
	const void loadIMG();
	sf::Sprite getSprite();
	sf::Texture getText() const;
	std::string getFile() const;
	sf::IntRect getRect() const;

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);


	virtual void updateRect(float elapsedTime);

	void updateDir(Direction dir);
	void changeAmtMove(int x);
	void updateMove(sf::Vector2f move);
	void setRotation(float rot);
	void setRotating(float deg, float distance, float speed);

	void setScale(float x, float y);



	sf::Vector2u getSize();
	sf::Vector2f getAmountMoved();
	sf::Vector2f getSector();


	void changePos(int x, int y);


protected:
	bool _rotating = false;

	float _deg = 0;
	float _distance = 0;
	float _rSpeed = 1;
	float _scaleX = 1;
	float _scaleY = 1;

	int _amtMove;
	int _maxMove;

	std::string _file;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::IntRect _rect;
	sf::Vector2f _move;
	sf::Vector2f _amountMoved;

	Direction _dirMove;

	sf::Vector2f _hbox;

private:
};

