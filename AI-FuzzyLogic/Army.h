#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <SFML/Graphics.hpp>

class Army
{
public:
	Army() = delete;
	Army(sf::Vector2f t_startPos, int t_force, double t_range, sf::Color t_col);

	void beginMoving();

	void update(sf::Time& t_dt);
	void render(sf::RenderWindow& t_window);

	void addSoldier();

private:

	sf::Vector2f m_startPos;
	sf::Color m_armyColor;
	double m_position;
	std::vector<sf::CircleShape> m_army;
	bool m_moving = false;

	float m_armySpeed = 50.0f;
	int m_troopOffsetY = 500;
};

#endif