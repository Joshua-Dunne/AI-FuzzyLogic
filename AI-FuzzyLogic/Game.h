#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fuzzy.h"
#include "Army.h"

class Game
{
public:
	Game();
	~Game();
private:
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;

public:
	void run();
	void processInput();
	void update(sf::Time& dt);
	void render();
	int getArmySize(float t_force, float t_range);

	float m_force = 10.0f, m_range = 25.0f;
	int m_sizeToSend = 0;

	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Font m_font;
	sf::Text m_information;

	Army* playerArmy;
	Army* enemyArmy;
};

#endif