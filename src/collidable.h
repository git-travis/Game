#pragma once
#include "rectIMG.h"
#include "item.h"
#include "ability.h"
#include "passive.h"
#include "shield.h"
#include "weapon.h"
#include "health.h"
#include "consumable.h"

#include <iosfwd>

class Collidable{
public:
	Collidable(std::string name);
	Collidable(std::string name, sf::Vector2f startCorner, sf::Vector2f endCorner);
	Collidable(std::string name, std::string filename, int xpos, int ypos, int xsize, int ysize);
	Collidable(std::string name, std::string filename, int xpos, int ypos, bool dest);
	Collidable();
	~Collidable();

	void build();

	void setDestructible(bool dest);
	void setLinkable(bool linkable);
	void destroy();
	void setFileName(std::string filename);

	void setSizeX(int size);
	void setSizeY(int size);
	void setPos(sf::Vector2f pos);

	sf::Vector2f getULCorner();
	sf::Vector2f getCentralPos();

	std::string getName();
	std::string getFilename();
	int getXSize();
	int getYSize();
	int getX();
	int getY();

	sf::Vector2f getSector();

	float getXLines();
	float getYLines();

	bool getDestructible();
	bool getLinkable();
	bool checkColl(sf::Vector2f pos);

	int getDropPos();
	void setDropPos(int pos);

	std::vector<sf::Sprite> getSpritesX();
	std::vector<sf::Sprite> getSpritesY();

	sf::Sprite getSprite();

	void update(float elapsedTime);
private:
	std::string _name;
	std::string _filename;
	sf::Texture _texture;
	rectIMG _sprite;

	int _sizeX = 0;
	int _sizeY = 0;
	int _dropPos = -1;

	sf::Vector2f _pos;
	sf::Vector2f _centralPos;

	bool _destructible = false;
	bool _linkable = true;
	bool _built = false;

	std::vector<sf::Sprite> _linksX;
	std::vector<sf::Sprite> _linksY;

};
