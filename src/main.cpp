//============================================================================
// Name        : Game.cpp
// Author      : Travis
// Version     : 0.5
//============================================================================


// '*' allows a variable to maintain manipulation when passed through a function instead of being a copy
// '&' is to reference

// '*' stores address, '&' references the address


#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <fmod_studio.hpp>
#include <fmod_studio_common.h>
#include <fmod_studio.h>

#include "game.h"
#include "Menus/menus.h"


inline sf::Vector2f mousexy(Game &game, sf::Vector2f &target, sf::Vector2f charPos){
	return game.getPlayerVector(charPos, target);
}


int main(){

	//leave trail of fire/lava/poison ability
	//greatsword that uses two clicks/inputs
	//add platforms that move character
	//add turrets
	//add enemies/ability that charges up for a bit then dashes forward
	//add flamethrower with flame trail

	//https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

	//
	//
	//CHANGE COLLISION TO RECTANGLES
	//
	//

	sf::Clock clock;
	float SCREENX = 1920;
	float SCREENY = 1080;
	bool clicked = false;
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "Demo");
    sf::Font font;
    sf::Text text;
    if(!font.loadFromFile("Fonts/aAtmospheric.ttf")){
    	std::cout << "COULD NOT LOAD FONT" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);

    bool paused = true;
    //use: window.create(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen); to recreate screen for fullscreen
    //use window.setVerticalSyncEnabled(true); for vsync option
    //window.setFramerateLimit(144);

    window.setMouseCursorVisible(false);
    //Game game;


    sf::Texture texture;
    rectIMG cursor = rectIMG("Sprites/SmallCursor.png");
    rectIMG BGimg = rectIMG("Sprites/space_bg1.png");
    BGimg.setScale(4, 4);
    std::vector<sf::Sprite> playerSprites;
    std::vector<sf::Sprite> enemySprites;
    std::vector<sf::Sprite> dropSprites;
    std::vector<sf::Text> guiText;


    sf::Vector2f mousexy2;
    sf::Vector2f playerPos;
    sf::Vector2f enemyPos;
    sf::Vector2f viewPos;

    Player player = Player("Player", "Sprites/Char.png");

    //player.loadIMG();
    player.setScale(0.5, 0.5);
    Player enemy = Player("enemy", "Sprites/Enemy_Char.png");
    //enemy.loadIMG();
    enemy.setScale(0.5, 0.5);

    //BGimg.loadIMG();
    //cursor.loadIMG();
    cursor.setScale(0.75, 0.75);
    /*
     * rectIMG chara = rectIMG("Char.png");
     * aniRectIMG spr = aniRectIMG("MyChar.png");
    chara.loadIMG();
    spr.loadIMG();
    spr.addAni(1, 0, 0, 150, 150);
    spr.addAni(1, 0, 16, 150, 150);
    spr.playAni(0);
    */





    sf::View view(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f, 1080.f)));
    window.setView(view);

    Game game;
    game.initALL();
    game.initPlayer(player);
    //game.loadPlayerFile();
    game.initEnemy(enemy);
    //game.loadEnemyFile();
    game.setEnemyPos(sf::Vector2f(250.0, 250.0));

    game.initPlayerItems();
    game.initEnemyItems();
    playerPos = game.getPlayerPos();
    viewPos = playerPos;
    int viewBoxXY[4] = {(SCREENX *.25), (SCREENY *.225), (SCREENX * .25), (SCREENY * .225)};
    //playerSprites = game.getPlayerSprites();

    //game.itemPickup(test, ability);
    //game.loadEnemyFile();
    //view.setSize(3840, 2160);


    float volume = 15;
	sf::Sound sound;
	sound.setVolume(15);
	sf::SoundBuffer pickupBuff;
	sf::SoundBuffer atkBuff;
	sf::SoundBuffer abilBuff;

	Menus menus;
	menus.initMenus();



    std::vector<sf::Sprite> XLinks = *game.getBuildingSprites();
    std::vector<sf::Sprite> Spawners = *game.getSpawnerSprites();


    game.update(clock.restart().asSeconds(), mousexy(game, mousexy2, playerPos), mousexy2, game.getRadians(playerPos, mousexy2), game.getPlayerAngle(playerPos, mousexy2), game.getPlayerAngle(enemyPos, playerPos), game.getRadians(enemyPos, playerPos), mousexy(game, playerPos, enemyPos));

    view.setCenter(viewPos);
    window.setView(view);

    while (window.isOpen()){
        sf::Event event;

        //player.rotate(10);


        //std::cout << clock.restart().asSeconds() << std::endl;

        while (window.pollEvent(event)){
        	mousexy2 = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        	switch (event.type){

        	case sf::Event::Closed:
        		window.close();
        		break;

        	case sf::Event::LostFocus:
        		//use to pause
        		paused = true;
        		break;

        	case sf::Event::KeyPressed:
        		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        			//chara.updateDir(UP);
        			game.movePlayer(UP);
        		}
        		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        			//chara.updateDir(DOWN);
        			game.movePlayer(DOWN);
        		}
        		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        			//chara.updateDir(LEFT);
        			game.movePlayer(LEFT);
        		}
        		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        			//chara.updateDir(RIGHT);
        			game.movePlayer(RIGHT);
        		}
        		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        			//chara.updateDir(RIGHT);
        			if(!paused){
            			abilBuff.loadFromFile(game.playerAbility());
            			sound.setBuffer(abilBuff);
            			sound.play();
        			}
        		}
        		if(event.key.code == sf::Keyboard::Escape){
        			if(paused){
            			paused = false;
            			window.setMouseCursorVisible(false);
        			}
        			else{
        				menus.pause();
            			paused = true;
        			}
        			//window.close();
        		}
        		break;

        		case sf::Event::KeyReleased:
        			if(event.key.code == sf::Keyboard::W){
        				//chara.updateDir(STOPU);
        				game.movePlayer(STOPU);
        			}
        			if(event.key.code == sf::Keyboard::S){
        				//chara.updateDir(STOPD);
        				game.movePlayer(STOPD);
        			}
        			if(event.key.code == sf::Keyboard::A){
        				//chara.updateDir(STOPL);
        				game.movePlayer(STOPL);
        			}
        			if(event.key.code == sf::Keyboard::D){
        				//chara.updateDir(STOPR);
        				game.movePlayer(STOPR);
        			}
        			if(event.key.code == sf::Keyboard::F){
        				pickupBuff.loadFromFile(game.itemPickup());
        				sound.setBuffer(pickupBuff);
        				sound.play();
        			}
        			//chara.updateDir(STOPPED);
        			break;

        		case sf::Event::MouseButtonPressed:
        			if(!paused){
                    	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    		atkBuff.loadFromFile(game.playerAttack(mousexy2));
                    		sound.setBuffer(atkBuff);
                    		sound.play();
                    	}
        			}
                	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){

                	}
        			//game.test();
        			break;

        		case sf::Event::MouseButtonReleased:
        			break;

        	default:
        		break;
        	}
        	//*/

        }

        //game.update(clock.getElapsedTime().asMicroseconds());
        //spr.playAni(0);
        //spr.update();
        //chara.updateRect();

        if(paused){
        	window.clear();
			window.setMouseCursorVisible(true);
			/*
			for(unsigned int i = 0; i < menuSprites.size(); i++){
				menuSprites[i].setPosition(viewPos.x, ((menuTexture.getSize().y * 1.1) * i) - 400 + viewPos.y);
			}*/
			/*
        	for(unsigned int i = 0; i < menuSprites.size(); i++){
        		window.draw(menuSprites.at(i));
        		text.setString(menuText[i]);
        		textRect = text.getLocalBounds();
        		text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        		text.setPosition(menuSprites.at(i).getPosition().x, menuSprites.at(i).getPosition().y);
        		window.draw(text);
        	}
        	*/
    		if(menus.update(clock.restart().asSeconds(), mousexy2, &viewPos, &game, &window, sf::Mouse::isButtonPressed(sf::Mouse::Left), event) == UNPAUSED){
    			paused = false;
    		}
            view.setCenter(viewPos);
            window.setView(view);
        	if(!clicked && sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        		/*
        		for(unsigned int i = 0; i < menuSprites.size(); i++){
        			//checks to see where the mouse was clicked in the menu
        			if((game.checkXColl(menuTexture.getSize().x / 4, mousexy2, menuSprites.at(i).getPosition())) && (game.checkYColl(menuTexture.getSize().y / 4, mousexy2, menuSprites.at(i).getPosition()))){
        				if(menuText.at(i) == "Resume"){
        					paused = false;
        					window.setMouseCursorVisible(false);
        				}
        				if(menuText.at(i) == "Level Editor"){



        					clicked = true;
        				}
        				if(menuText.at(i) == "Volume +"){
        					volume += 5;
        					music.setVolume(volume);
        					clicked = true;
        				}
        				if(menuText.at(i) == "Volume -"){
        					volume -= 5;
        					music.setVolume(volume);
        					clicked = true;
        				}
        				if(menuText.at(i) == "Quit"){
        					window.close();
        				}
        			}
        		}
        		*/
        	}
        	if(event.type == sf::Event::MouseButtonReleased){
        		clicked = false;
        	}
        }
        else{
        	game.enemyAttack();

            playerPos = game.getPlayerPos();
            enemyPos = game.getEnemyPos();

            game.update(clock.restart().asSeconds(), mousexy(game, mousexy2, playerPos), mousexy2, game.getRadians(playerPos, mousexy2), game.getPlayerAngle(playerPos, mousexy2), game.getPlayerAngle(enemyPos, playerPos), game.getRadians(enemyPos, playerPos), mousexy(game, playerPos, enemyPos));
            playerPos = game.getPlayerPos();

            //the holy view code
            if(playerPos.x > viewPos.x + viewBoxXY[0]){
            	viewPos.x = playerPos.x - viewBoxXY[0];
            }
            if(playerPos.y > viewPos.y + viewBoxXY[1]){
            	viewPos.y = playerPos.y - viewBoxXY[1];
            }
            if(playerPos.x < viewPos.x - viewBoxXY[2]){
            	viewPos.x = playerPos.x + viewBoxXY[2];
            }
            if(playerPos.y < viewPos.y - viewBoxXY[3]){
            	viewPos.y = playerPos.y + viewBoxXY[3];
            }
            view.setCenter(viewPos);
            window.setView(view);


            window.clear();
            window.draw(*BGimg.getSprite());

            //window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x - 100, sf::Mouse::getPosition(window).y - 100))
            //game.setWPos(sf::Vector2f(game.getPlayer().getPos().x - 75, game.getPlayer().getPos().y + 75));
            //game.setSPos(sf::Vector2f(game.getPlayer().getPos().x + (game.getPlayer().getSize().x * 1.5) * -mousexy.x, game.getPlayer().getPos().y + (game.getPlayer().getSize().y * 1.5) * -mousexy.y));
            //game.setWPos(sf::Vector2f(game.getPlayer().getPos().x + (game.getPlayer().getSize().x * (1.15)) * (mousexy.x), game.getPlayer().getPos().y + (game.getPlayer().getSize().y * (1.15)) * (mousexy.y)));

            cursor.setPos(window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)));


            playerSprites = game.getPlayerSprites();
            for(unsigned i = 0; i < playerSprites.size(); i++){
            	window.draw(playerSprites[i]);
            }
            enemySprites = game.getEnemySprites();
            for(unsigned i = 0; i < enemySprites.size(); i++){
            	window.draw(enemySprites[i]);
            }
            dropSprites = game.getDropSprites();
            for(unsigned i = 0; i < dropSprites.size(); i++){
            	window.draw(dropSprites[i]);
            }

            for(unsigned i = 0; i < XLinks.size(); i++){
            	window.draw(XLinks[i]);
            }
            for(unsigned i = 0; i < Spawners.size(); i++){
            	window.draw(Spawners[i]);
            }

            //
            guiText = game.getGuiText(&text, viewPos);
            for(unsigned i = 0; i < guiText.size(); i++){
            	window.draw(guiText[i]);
            }



            window.draw(*cursor.getSprite());

            //window.draw(spr.getSprite());
            //window.draw(chara.getSprite());
            //window.draw(sprite);
            //window.draw(shape);
        }

        window.display();
    }

    return 0;
}
