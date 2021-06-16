#pragma once
#include <SFML/Audio.hpp>
#include <iosfwd>

#include "player.h"
#include "map.h"

class Graphics;

class Game {
public:
	Game();
	~Game();

	sf::Vector2f getPlayerPos();
	sf::Vector2f getEnemyPos();

	void initPlayer(std::string name, int x, int y, int width, int height, std::string filename);
	void initPlayer(Player player);
	//void initPlayer(Player player, Ability* ability, Passive* passive, Shield* shield, Weapon* weapon);
	void initEnemy(std::string name, int x, int y, int width, int height, std::string filename);
	void initEnemy(Player enemy);
	//void initEnemy(Player player, Ability ability, Passive* passive, Shield shield, Weapon* weapon);
	void addChar(std::string name, int x, int y, int width, int height, std::string filename);
	void addChar(Player chara);

	void initPlayerItems();
	void initEnemyItems();

	void movePlayer(Direction dir);
	void setPlayerPos(sf::Vector2f pos);
	void moveEnemy(Direction dir);
	void setEnemyPos(sf::Vector2f pos);

	void initItems();
	void initAbilities();
	void initPassives();
	void initShields();
	void initWeapons();
	void initHealth();
	void initBorders(std::string file);
	void initConsumables();
	void initMaps();
	void initAlive();
	void initDrops();
	void initALL();

	void test();

	void setPlayerRotation(float rot);

	float getPlayerAngle(sf::Vector2f charPos, sf::Vector2f obj);
	float getRadians(sf::Vector2f charPos, sf::Vector2f obj);
	sf::Vector2f getPlayerVector(sf::Vector2f charPos, sf::Vector2f obj);

	std::vector<sf::Sprite> getPlayerSprites();
	std::vector<sf::Sprite> getEnemySprites();
	std::vector<sf::Sprite>* getBuildingSprites();
	std::vector<sf::Sprite>* getSpawnerSprites();
	std::vector<sf::Text> getGuiText(sf::Text * txt, sf::Vector2f view);

	Player getPlayer();

	void loadPlayerFile();
	void loadEnemyFile();
	void loadCharFile();

	inline sf::Vector2f normalize(sf::Vector2f point);
	sf::Vector2f getAmountPlayerMoved();

	void genPlayer();
	void genEnemy();

	std::string playerAttack(sf::Vector2f mouse);
	std::string playerAbility();
	void playerPickup(Item *item);


	void playerDrop(itemType type);
	void enemyAttack();
	void enemyAbility();

	void setPaused(bool pause);
	bool getPaused();
	float getVolume();
	void setVolume(float amt);
	sf::Music* getMusic();
	void setMusic(std::string filename);

	bool checkColl(Player & player, Player & enemy);
	bool checkColl(Player & player, Projectile & projectile);
	bool checkColl(Player & player, int range);
	bool checkColl(Player & player, sf::Vector2f pos);
	bool checkXColl(int size, sf::Vector2f pos1, sf::Vector2f pos);
	bool checkYColl(int size, sf::Vector2f pos1, sf::Vector2f pos);

	std::string itemPickup();

	void update(float elapsedTime, sf::Vector2f mouse, sf::Vector2f mousepos, float rads, float mouseAngle, float playerAngle, float enemyRads, sf::Vector2f playerxy);

	std::vector<Item*> getDrops();
	std::vector<sf::Sprite> getDropSprites();

private:
	bool _paused = true;
	float _volume = 15;

	float _timeTracker = 0;
	float _dxTracker;
	float _dyTracker;
	float _distTracker;
	float _radians;
	float _norm;

	sf::Music _music;

	Player _player;
	Player _enemy;
	std::vector<Player> _alive;

	std::vector<Item*> _drops;
	std::vector<Passive> _passives;
	std::vector<Weapon> _weapons;
	std::vector<Ability> _abilities;
	std::vector<Shield> _shields;
	std::vector<Projectile> _projectiles;
	std::vector<Health> _healths;
	std::vector<Consumable> _consumables;

	std::vector<sf::Sprite> _borders;
	sf::Texture _borderTexture;
	sf::Sprite _borderSprite;

	rectIMG _border = rectIMG("Sprites/Border.png");

	std::vector<sf::Sprite> _sprites;
	std::vector<sf::Sprite> _spawnables;
	std::vector<sf::Sprite> _dropSprites;

	Map _map = Map();

};

