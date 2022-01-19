#include "Army.h"

/// <summary>
/// Create an Army of certain size at a specific position.
/// The Army is also given the position they should move to.
/// </summary>
/// <param name="t_startPos">Where the Army starts</param>
/// <param name="t_force">Size of Army</param>
/// <param name="t_range">Where Army moves to</param>
/// <param name="t_col">Color of Army</param>
Army::Army(sf::Vector2f t_startPos, int t_force, double t_range, sf::Color t_col) : 
	m_position(t_range), m_startPos(t_startPos), m_armyColor(t_col)
{
	for (int i = 0; i < t_force; i++)
	{
		sf::CircleShape soldier;
		soldier.setFillColor(t_col);
		soldier.setRadius(10.0f);
		soldier.setOrigin(sf::Vector2f{ 5.0f, 5.0f });

		int xOffset = rand() % 50 + 1, yOffset = (rand() % (m_troopOffsetY)+1) - m_troopOffsetY / 2;

		soldier.setPosition(t_startPos + sf::Vector2f{ static_cast<float>(xOffset), static_cast<float>(yOffset) });

		m_army.push_back(soldier);
	}
}

void Army::beginMoving()
{
	m_moving = true;
}

void Army::update(sf::Time& t_dt)
{
	if (m_moving)
	{
		for (auto& soldier : m_army)
		{
			if (soldier.getPosition().x < m_position)
			{
				soldier.move(sf::Vector2f{ (m_armySpeed * t_dt.asSeconds()), 0 });

				if (soldier.getPosition().x > m_position - 2.0f)
				{
					m_moving = false;
					break;
				}
			}
			else if (soldier.getPosition().x > m_position)
			{
				soldier.move(sf::Vector2f{ -(m_armySpeed * t_dt.asSeconds()), 0 });

				if (soldier.getPosition().x < m_position + 2.0f)
				{
					m_moving = false;
					break;
				}
			}
		}
	}
}

void Army::render(sf::RenderWindow& t_window)
{
	for (auto& soldier : m_army)
	{
		t_window.draw(soldier);
	}
}

void Army::addSoldier()
{
	sf::CircleShape soldier;
	soldier.setFillColor(m_armyColor);
	soldier.setRadius(10.0f);
	soldier.setOrigin(sf::Vector2f{ 5.0f, 5.0f });

	int xOffset = rand() % 50 + 1, yOffset = (rand() % (m_troopOffsetY) + 1) - m_troopOffsetY / 2;

	soldier.setPosition(m_startPos + sf::Vector2f{ static_cast<float>(xOffset), static_cast<float>(yOffset) });

	m_army.push_back(soldier);
}
