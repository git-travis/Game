#include "game.h"

#include <iostream>
#include <cmath>

Game::Game(){
}

Game::~Game(){}

sf::Vector2f Game::getPlayerPos(){
	return _player.getPos();
}
sf::Vector2f Game::getAmountPlayerMoved(){
	return _player.getAmountMoved();
}
sf::Vector2f Game::getEnemyPos(){
	return _enemy.getPos();
}

inline sf::Vector2f Game::normalize(sf::Vector2f point){
	_norm = sqrt(pow(point.x, 2) + pow(point.y, 2));
	//std::cout << "" << point.x << std::endl;
	return sf::Vector2f((point.x / _norm), (point.y / _norm));
}

void Game::initPlayer(std::string name, int x, int y, int width, int height, std::string filename){
	_player = Player(name,  filename);
	//_player.loadIMG();
}
void Game::initPlayer(Player player){
	_player = player;
	//_player.loadIMG();
}/*
void Game::initPlayer(Player player, Ability* ability, Passive* passive, Shield* shield, Weapon* weapon){
	_player = player;
	_player.setAbility(ability);
	_player.setPassive(passive);
	_player.setShield(shield);
	_player.setWeapon(weapon);
}*/
void Game::initEnemy(std::string name, int x, int y, int width, int height, std::string filename){
	_enemy = Player(name, filename);
	//_enemy.loadIMG();
	//_enemy.setScale(0.5, 0.5);
}
void Game::initEnemy(Player enemy){
	_enemy = enemy;
	//_alive.push_back(enemy);
	//_enemy.loadIMG();
	//_enemy.setScale(0.5, 0.5);
}/*
void Game::initEnemy(Player player, Ability ability, Passive* passive, Shield shield, Weapon* weapon){

}*/
void Game::addChar(std::string name, int x, int y, int width, int height, std::string filename){
	_alive.push_back(Player(name, filename));
}
void Game::addChar(Player chara){
	_alive.push_back(chara);
}




void Game::loadEnemyFile(){
	_enemy.loadIMG();
}

void Game::loadPlayerFile(){
	_player.loadIMG();
}
void Game::loadCharFile(){
	for(unsigned i = 0; i < _alive.size(); i++){
		_alive.at(i).loadIMG();
	}
}

//initialize all things in the game
void Game::initItems(){

}
void Game::initAbilities(){
	_abilities.push_back(Ability(HEAL, "Heal", 0, 33, 0, 10, "Sprites/Healing_Hearts.png", "Audio/Healing_pickup.ogg", "Audio/Healing_Use.ogg"));
	_abilities.push_back(Ability(DAMAGE, "Spark", 5, 0, 5, 5, "Sprites/Heart_Sparks.png"));
	_abilities.push_back(Ability(MOVEMENT, TELEPORT, "Tele", 0, 100, 0, 2, "Sprites/Teleporter.png", "Sprites/Teleporter_Position.png", "Audio/Teleport_Pickup.ogg", "Audio/Teleport_Use.ogg"));
	_abilities.at(2).setPos(sf::Vector2f(0, -100));
	for(unsigned i = 0; i < _abilities.size(); i++){
		_abilities.at(i).loadAbility();
		_abilities.at(i).setScale(0.4, 0.4);
	}
}
void Game::initPassives(){
	_passives.push_back(Passive(HEAL, "Restore", 25, 0, 0, "Sprites/Shield_Restore.png"));
	_passives.push_back(Passive(DAMAGE, "Thorns", 25, 0, 0, "Sprites/Shield_Spikes.png"));
	for(unsigned i = 0; i < _passives.size(); i++){
		_passives.at(i).loadIMG();
		_passives.at(i).setScale(0.4, 0.4);
	}
}
void Game::initShields(){
	_shields.push_back(Shield("Basic", 100, "Sprites/Shield_High.png"));
	_shields.push_back(Shield("Basic", 60, "Sprites/Shield_Mid.png"));
	_shields.push_back(Shield("Basic", 30, "Sprites/Shield_Low.png"));
	for(unsigned i = 0; i < _shields.size(); i++){
		_shields.at(i).loadIMG();
		_shields.at(i).setScale(0.4, 0.4);
	}
}
void Game::initWeapons(){
	_weapons.push_back(Weapon("Laser Dagger", 75, 0, 1.5, 6, MELEE, "Sprites/Laser_Dagger_Right.png", "Audio/Laser_Dagger_Pickup.ogg", "Audio/Laser_Dagger_Attack.ogg"));
	_weapons.at(0).setScale(0.55, 0.55);
	_weapons.push_back(Weapon("Katana", 100, 0, 1.75, 8, MELEE, "Sprites/Katana_Right.png"));
	_weapons.at(1).setScale(0.65, 0.65);
	_weapons.push_back(Weapon("Blaster", 75, 0, 1.5, 6, 750, PROJECTILE, "Sprites/Blaster.png", "Sprites/Bullet.png", "Audio/Laser_Pickup.ogg", "Audio/Classic_Laser.ogg"));
	_weapons.at(2).setScale(0.75, 0.75);
	_weapons.at(2).setPos(sf::Vector2f(200, -100));
	for(unsigned i = 0; i < _weapons.size(); i++){
		_weapons.at(i).loadIMG();
		_weapons.at(i).loadProjIMG();
	}
}

void Game::initHealth(){
	_healths.push_back(Health("Health100", 100, "Sprites/Heart_High.png"));
	_healths.push_back(Health("Health60", 60, "Sprites/Heart_Mid.png"));
	_healths.push_back(Health("Health30", 30, "Sprites/Heart_Low.png"));
	for(unsigned i = 0; i < _healths.size(); i++){
		_healths.at(i).loadIMG();
		_healths.at(i).setScale(0.4, 0.4);
	}
}

void Game::initBorders(std::string file){
	_borderTexture.loadFromFile(file);
	for(int i = 0; i < 20; i++){
		_borderSprite = sf::Sprite(_borderTexture);
		_borderSprite.setOrigin(_borderTexture.getSize().x / 2, _borderTexture.getSize().y / 2);
		_borderSprite.setScale(0.45, 0.45);
		_borders.push_back(_borderSprite);
	}
}
void Game::initConsumables(){
	_consumables.push_back(Consumable("Insta-Health", "Sprites/Health_Bandaid.png"));
	_consumables.push_back(Consumable("Insta-Shield", "Sprites/Shield_Bandaid.png"));
	//_consumables.push_back(Consumable("Nade", "Grenade.png"));
	for(unsigned i = 0; i < _consumables.size(); i++){
		_consumables.at(i).loadIMG();
		_consumables.at(i).setScale(0.4, 0.4);
	}
}
void Game::initDrops(){
	_drops.push_back(&_abilities[2]);
	_drops.push_back(&_weapons[2]);


	for(unsigned i = 0; i < _drops.size(); i++){
		_dropSprites.push_back(_drops.at(i)->getSprite());
	}
}



void Game::initALL(){
	//setMusic("Audio/Music.ogg");
	initItems();
	initAbilities();
	initPassives();
	initShields();
	initWeapons();
	initHealth();
	initBorders("Sprites/Border.png");
	initConsumables();
	initMaps();
	initAlive();
	initDrops();
}

void Game::initPlayerItems(){
	_player.setAbility(&_abilities.at(0));
	_player.setPassive(&_passives.at(0));
	//_player.setShield(&_shields.at(1));
	_player.setWeapon(&_weapons.at(0));
	_player.setHealth(&_healths.at(2));
	_player.setConsumable(&_consumables.at(0));
	_player.update(0, sf::Vector2f(0,0), sf::Vector2f(0,0), 0, 0);
}
void Game::initEnemyItems(){
	_enemy.setAbility(&_abilities.at(1));
	_enemy.setPassive(&_passives.at(1));
	//_enemy.setShield(&_shields.at(1));
	_enemy.setWeapon(&_weapons.at(1));
	//_enemy.setHealth(&_healths.at(1));
	_enemy.setConsumable(&_consumables.at(1));
	_enemy.update(0, sf::Vector2f(0,0), sf::Vector2f(0,0), 0, 0);
}

void Game::initMaps(){
	std::vector<std::string> maps = _map.getMapList();
	_map.load(maps.at(rand() % maps.size()));
	/*
	_structure = Collidable("Building", "Sprites/Wall_Link.png", -1000, -500, 5, 3);
	_structure.build();
	_structuresX = _structure.getSpritesX();
	_structuresY = _structure.getSpritesY();
	*/
	//_structures.push_back(Collidable("Barrel", "Sprites/Barrel.png", -1000, -500, true));
	//_structuresX.push_back(_structures[0].getSprite());
}

std::vector<sf::Sprite>* Game::getBuildingSprites(){

	return _map.getStructureSprites();
}
std::vector<sf::Sprite>* Game::getSpawnerSprites(){
	return _map.getSpawnerSprites();
}
std::vector<sf::Sprite> Game::getDropSprites(){
	return _dropSprites;
}

void Game::initAlive(){
	_alive.push_back(_player);
	_alive.push_back(_enemy);
}

std::vector<sf::Sprite> Game::getPlayerSprites(){
	_sprites.clear();
	_spawnables = _player.getSpawnables();

	_sprites.push_back(_player.getSprite());
	_borders.at(0).setPosition(_player.getHealthSprite().getPosition());
	_sprites.push_back(_borders.at(0));
	_sprites.push_back(_player.getHealthSprite());
	_borders[1].setPosition(_player.getShieldSprite().getPosition());
	_sprites.push_back(_borders.at(1));
	_sprites.push_back(_player.getShieldSprite());
	_borders[2].setPosition(_player.getConsumableSprite().getPosition());
	_sprites.push_back(_borders[2]);
	_sprites.push_back(_player.getConsumableSprite());
	_sprites.push_back(_player.getWeaponSprite());
	_sprites.push_back(_player.getAbilitySprite());
	_sprites.push_back(_player.getPassiveSprite());

	if(_spawnables.size() > 0){
		for(unsigned i = 0; i < _spawnables.size(); i++){
			_sprites.push_back(_spawnables[i]);
		}
	}
	if(_projectiles.size() > 0){
		for(unsigned i = 0; i < _projectiles.size(); i++){
			_sprites.push_back(_projectiles[i].getSprite());
		}
	}

	return _sprites;
}
std::vector<sf::Sprite> Game::getEnemySprites(){
	_sprites.clear();
	_spawnables = _enemy.getSpawnables();

	_sprites.push_back(_enemy.getSprite());
	_borders.at(3).setPosition(_enemy.getHealthSprite().getPosition());
	_sprites.push_back(_borders.at(3));
	_sprites.push_back(_enemy.getHealthSprite());
	_borders[4].setPosition(_enemy.getShieldSprite().getPosition());
	_sprites.push_back(_borders.at(4));
	_sprites.push_back(_enemy.getShieldSprite());
	_borders[5].setPosition(_enemy.getConsumableSprite().getPosition());
	_sprites.push_back(_borders[5]);
	_sprites.push_back(_enemy.getConsumableSprite());
	_sprites.push_back(_enemy.getWeaponSprite());
	_sprites.push_back(_enemy.getAbilitySprite());
	_sprites.push_back(_enemy.getPassiveSprite());

	if(_spawnables.size() > 0){
		for(unsigned i = 0; i < _spawnables.size(); i++){
			_sprites.push_back(_spawnables[i]);
		}
	}

	return _sprites;
}

std::vector<sf::Text> Game::getGuiText(sf::Text * txt, sf::Vector2f view){
	std::vector<sf::Text> texts;
	static sf::FloatRect textRect;
	txt->setString("Shield: " +  std::to_string((int) _player.getShield().getRemaining()));
	textRect = txt->getLocalBounds();
	txt->setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	txt->setPosition(view.x - 500, view.y + 500);
	texts.push_back(*txt);
	txt->setString("Health: " +  std::to_string((int) _player.getHealth().getRemaining()));
	textRect = txt->getLocalBounds();
	txt->setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	txt->setPosition(view.x - 800, view.y + 500);
	texts.push_back(*txt);

	return texts;
}




void Game::movePlayer(Direction dir){
	_player.updateDir(dir);
}

void Game::moveEnemy(Direction dir){
	_enemy.updateDir(dir);
}


void Game::setPlayerPos(sf::Vector2f v2){
	_player.setPos(v2);
}
void Game::setEnemyPos(sf::Vector2f v2){
	_enemy.setPos(v2);
}

Player Game::getPlayer(){
	return this->_player;
}
void Game::setPaused(bool paused){
	_paused = paused;
}

bool Game::getPaused(){
	return _paused;
}
float Game::getVolume(){
	return _volume;
}
void Game::setVolume(float amt){
	_volume = amt;
}
sf::Music* Game::getMusic(){
	return &_music;
}
void Game::setMusic(std::string filename){
    if(!_music.openFromFile("filename")){
    	std::cout << "UNABLE TO OPEN MUSIC" << std::endl;
    }
    _music.setLoop(true);
    _music.setVolume(_volume);
    //_music.play();
}
bool Game::checkColl(Player & player, Player & enemy){
	_dxTracker = player.getPos().x - enemy.getPos().x;
	_dyTracker = player.getPos().y - enemy.getPos().y;
	_distTracker = _dxTracker * _dxTracker + _dyTracker * _dyTracker;

	return _distTracker < std::pow(player.getSize().x, 2);
}
bool Game::checkColl(Player & player, Projectile & projectile){
	//std::cout << "thinasgdj" << std::endl;
	/*
	if(player.getPos().x < projectile.getPos().x + projectile.getSize().x &&
			player.getPos().x + player.getSize().x > projectile.getPos().x &&
			player.getPos().y < projectile.getPos().y + projectile.getSize().y &&
			player.getPos().y + player.getSize().y > projectile.getPos().y){
		return true;
	}
	return false;
	*/
	_dxTracker = player.getPos().x - projectile.getPos().x;
	_dyTracker = player.getPos().y - projectile.getPos().y;
	_distTracker = _dxTracker * _dxTracker + _dyTracker * _dyTracker;

	return (_distTracker < std::pow(player.getSize().x + projectile.getSize().x, 2));
}
bool Game::checkColl(Player & player, sf::Vector2f pos){
	_dxTracker = player.getPos().x - pos.x;
	_dyTracker = player.getPos().y - pos.y;
	_distTracker = _dxTracker * _dxTracker + _dyTracker * _dyTracker;

	return (_distTracker < std::pow(player.getSize().x, 2));
}
bool Game::checkXColl(int size, sf::Vector2f pos1, sf::Vector2f pos){
	_dxTracker = pos1.x - pos.x;
	_distTracker = _dxTracker * _dxTracker;

	return (_distTracker < std::pow(size, 2));
}
bool Game::checkYColl(int size, sf::Vector2f pos1, sf::Vector2f pos){
	_dyTracker = pos1.y - pos.y;
	_distTracker = _dyTracker * _dyTracker;

	return (_distTracker < std::pow(size, 2));
}






float Game::getPlayerAngle(sf::Vector2f charPos, sf::Vector2f obj){
	//float radians = atan2((obj.y - charPos.y) , (obj.x - charPos.x));
	return atan2((obj.y - charPos.y) , (obj.x - charPos.x)) * 180 / 3.14159265;
}
sf::Vector2f Game::getPlayerVector(sf::Vector2f charPos, sf::Vector2f obj){
	_radians = atan2((obj.y - charPos.y) , (obj.x - charPos.x));
	return sf::Vector2f(cos(_radians), sin(_radians));
}
float Game::getRadians(sf::Vector2f charPos, sf::Vector2f obj){
	//float radians = atan2((obj.y - charPos.y) , (obj.x - charPos.x));
	return atan2((obj.y - charPos.y) , (obj.x - charPos.x));
}

void Game::test(){
}

std::vector<Item*> Game::getDrops(){
	return _drops;
}


std::string Game::playerAttack(sf::Vector2f mouse){
	switch(_player.getWeapon().getWType()){
	case MELEE:
		break;

	case PROJECTILE:
		_projectiles.push_back(_player.getProjectile(normalize(sf::Vector2f(mouse.x - _player.getWeapon().getPos().x, mouse.y - _player.getWeapon().getPos().y))));
		break;

	case HITSCAN:
		break;

	default:
		break;
	}
	_player.attack();
	return _player.getWeapon().getUse();
}
std::string Game::playerAbility(){
	_player.triggerAbility();
	return _player.getAbility().getUse();
}
void Game::playerPickup(Item *item){

	playerDrop(item->getType());

	switch(item->getType()){
	case ABILITY:
		_player.setAbility((Ability*)item);
		break;

	case PASSIVE:
		_player.setPassive((Passive*)item);
		break;

	case SHIELD:
		_player.setShield((Shield*)item);
		break;

	case WEAPON:
		_player.setWeapon((Weapon*)item);
		break;

	case HEALTH:
		_player.setHealth((Health*)item);
		break;

	default:
		break;
	}
}
void Game::playerDrop(itemType type){
	switch(type){
	case ABILITY:
		//these for loops are a temporary fix. The Player class should be holding pointers to avoid this
		for(unsigned i = 0; i < _abilities.size(); i++){
			if(_abilities.at(i).getName() == _player.getAbility().getName()){
				_abilities.at(i).setPos(_player.getPos());
				_dropSprites.push_back(_abilities.at(i).getSprite());
				_drops.push_back(&_abilities.at(i));
			}
		}
		break;

	case PASSIVE:
		for(unsigned i = 0; i < _passives.size(); i++){
			if(_passives.at(i).getName() == _player.getPassive().getName()){
				_passives.at(i).setPos(_player.getPos());
				_dropSprites.push_back(_passives.at(i).getSprite());
				_drops.push_back(&_passives.at(i));
			}
		}
		break;

	case SHIELD:
		for(unsigned i = 0; i < _shields.size(); i++){
			if(_shields.at(i).getName() == _player.getShield().getName()){
				_shields.at(i).setPos(_player.getPos());
				_dropSprites.push_back(_shields.at(i).getSprite());
				_drops.push_back(&_shields.at(i));
			}
		}
		break;

	case WEAPON:
		for(unsigned i = 0; i < _weapons.size(); i++){
			if(_weapons.at(i).getName() == _player.getWeapon().getName()){
				_weapons.at(i).setPos(_player.getPos());
				_dropSprites.push_back(_weapons.at(i).getSprite());
				_drops.push_back(&_weapons.at(i));
			}
		}
		break;

	case HEALTH:
		for(unsigned i = 0; i < _healths.size(); i++){
			if(_healths.at(i).getName() == _player.getHealth().getName()){
				_healths.at(i).setPos(_player.getPos());
				_dropSprites.push_back(_healths.at(i).getSprite());
				_drops.push_back(&_healths.at(i));
			}
		}
		break;

	default:
		break;
	}
}

void Game::enemyAttack(){
	_enemy.attack();
}
void Game::enemyAbility(){
	_enemy.triggerAbility();
}


void Game::setPlayerRotation(float rot){
	_player.setRotation(rot);
}
std::string Game::itemPickup(){
	std::string temp;
	bool once = true;
	if(_drops.size() > 0){
		for(unsigned i = 0; i < _drops.size() && once; i++){
			if(checkColl(_player, _drops.at(i)->getPos())){
				playerDrop(_drops[i]->getType());
			    switch(_drops[i]->getType()){
			    	case ABILITY:
			    		_player.setAbility((Ability*)_drops[i]);
			    		temp = _player.getAbility().getPickup();
			    		break;

			    	case PASSIVE:
			    		_player.setPassive((Passive*)_drops[i]);
			    		temp = _player.getPassive().getPickup();
			    		break;

			    	case SHIELD:
			    		_player.setShield((Shield*)_drops[i]);
			    		temp = _player.getShield().getPickup();
			    		break;

			    	case WEAPON:
			    		_player.setWeapon((Weapon*)_drops[i]);
			    		temp = _player.getWeapon().getPickup();
			    		break;

			    	case HEALTH:
			    		_player.setHealth((Health*)_drops[i]);
			    		temp = _player.getHealth().getPickup();
			    		break;

			    	default:
			    		temp = "Audio/filler.ogg";
			    		break;
			    	}
			    _dropSprites.erase(_dropSprites.begin() + i, _dropSprites.begin() + i + 1);
			    _drops.erase(_drops.begin() + i, _drops.begin() + i + 1);
			    once = false;
			}
		}
	}
	return temp;
}


void Game::update(float elapsedTime, sf::Vector2f mouse, sf::Vector2f mousepos, float rads, float mouseAngle, float playerAngle, float enemyRads, sf::Vector2f playerxy){

	//check if entities are overlapping
	if(checkColl(_player, _enemy)){
		_player.move(sf::Vector2f((_player.getPos().x - _enemy.getPos().x), (_player.getPos().y - _enemy.getPos().y)), elapsedTime);
		_enemy.move(sf::Vector2f((_player.getPos().x - _enemy.getPos().x) * -1, (_player.getPos().y - _enemy.getPos().y)  * -1), elapsedTime);
	}
	/*
	for(int i = 0; i < _alive.size(); i++){
		if(_alive.at(i).getAttacking()){
			sf::Vector2f pos = _alive.at(i).getWeapon().getPos();
			std::vector<int> nums = _sectors[sf::Vector2f(pos.x / 600, pos.y / 600)];
			for(int k = 0; k < nums.size(); k++){
				if(checkColl(_alive.at(nums.at(k)), _alive.at(i).getWeapon().getPos())){
					if(_alive.at(nums.at(k)).hurt(_alive.at(i).getWeapon().getDmg() * elapsedTime) <= 0){
						std::cout << "DEAD" << std::endl;
					}
				}
			}
		}
	}
	*/

	//simple attack checks, need to update this to a vector of entities or something and iterate through it instead of this
	if(_enemy.getAttacking()){
		if(checkColl(_player, _enemy.getWeapon().getPos())){
			if(_player.hurt(_enemy.getWeapon().getDmg() * elapsedTime) <= 0){
				//std::cout << "PLAYER DEAD" << std::endl;
			}
		}
	}

	if(_player.getAttacking()){
		if(checkColl(_enemy, _player.getWeapon().getPos())){
			if(_enemy.hurt(_player.getWeapon().getDmg() * elapsedTime) <= 0){
				//std::cout << "ENEMY DEAD" << std::endl;
			}
		}
	}

	//check collision with structures, probably needs to be reworked
	for(unsigned i = 0; i < _map.getStructures().size(); i++){
		if(_map.getStructures()[i].checkColl(_player.getPos())){
			_player.move(sf::Vector2f((_player.getPos().x - _map.getStructures()[i].getCentralPos().x), (_player.getPos().y - _map.getStructures()[i].getCentralPos().y)), elapsedTime * 10);
		}
	}

	if(_projectiles.size() > 0){
		for(unsigned i = 0; i < _projectiles.size(); i++){
			_projectiles.at(i).update(elapsedTime);
			//need to change sector check to include length/width of objects to get what sectors they may bleed into
			if(((_enemy.getSector().x + 1) >= _projectiles.at(i).getSector().x && (_enemy.getSector().x - 1) <= _projectiles.at(i).getSector().x) &&
				(_enemy.getSector().y + 1) >= _projectiles.at(i).getSector().y && (_enemy.getSector().y - 1) <= _projectiles.at(i).getSector().y){
				std::cout << "In Sector" << std::endl;
				if(checkColl(_enemy, _projectiles.at(i))){
					_enemy.hurt(_projectiles.at(i).getDmg() * elapsedTime);
					std::cout << "working" << std::endl;
				}
			}
			/*
			for(int k = 0; k < _alive.size(); k++){
				if(_alive.at(k).getSector().x == _projectiles.at(i).getSector().x && _alive.at(k).getSector().y == _projectiles.at(i).getSector().y){
					if(checkColl(_alive.at(k), _projectiles.at(i))){
						_alive.at(k).hurt(_projectiles.at(i).getDmg() * elapsedTime);
						std::cout << "working" << std::endl;
					}
				}
			}
			*/
		}
		for(unsigned i = 0; i < _projectiles.size(); i++){
			if(abs(_projectiles.at(i).getPos().x) > 1500 || abs(_projectiles.at(i).getPos().y) > 1500){
				_projectiles.erase(_projectiles.begin());
			}
		}
	}
	if(_player.isAlive()){
		_player.update(elapsedTime, mouse, mousepos, rads, mouseAngle);
	}
	if(_enemy.isAlive()){
		_enemy.update(elapsedTime, playerxy, getPlayerPos(), enemyRads, playerAngle);
	}
}
