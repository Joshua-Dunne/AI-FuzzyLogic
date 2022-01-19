#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fuzzy.h"

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
	double getArmySize(double t_force, double t_range);

	double m_force = 8.0, m_range = 25.0, m_sizeToSend = 0.0;
};

#endif