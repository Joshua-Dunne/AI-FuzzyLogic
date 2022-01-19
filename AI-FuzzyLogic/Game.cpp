#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(800u, 600u), "Lab1")
{
	//m_window.setFramerateLimit(60u);

	m_sizeToSend = getArmySize(m_force, m_range);
}

Game::~Game()
{
}

/// <summary>
/// Run the main Game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen())
	{
		processInput();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// Processes inputs from Events
/// </summary>
void Game::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements

	m_window.display();
}

double Game::getArmySize(double t_force, double t_range)
{
	double m_Tiny = 0.0, m_Small = 0.0, m_Moderate = 0.0, m_Large = 0.0;
	double m_Close = 0.0, m_Medium = 0.0, m_Far = 0.0;
	double m_lowVal = 0.0, m_mediumVal = 0.0, m_highVal = 0.0;

	// Fuzzy Variables Setup & Fuzzification
	// Force
	m_Tiny = FuzzyLogic::Triangle(t_force, -10.0, 0.0, 10.0);
	m_Small = FuzzyLogic::Trapezoid(t_force, 2.5, 10.0, 15.0, 20.0);
	m_Moderate = FuzzyLogic::Trapezoid(t_force, 15.0, 20.0, 25.0, 30.0);
	m_Large = FuzzyLogic::Grade(t_force, 25.0, 30.0);

	// Range
	m_Close = FuzzyLogic::Triangle(t_range, -30.0, 0.0, 30.0);
	m_Medium = FuzzyLogic::Trapezoid(t_range, 10.0, 30.0, 50.0, 70.0);
	m_Far = FuzzyLogic::Grade(t_range, 50.0, 70.0);

	// Rules Matrix & Application
	m_lowVal = FuzzyLogic::OR(FuzzyLogic::AND(m_Medium, m_Tiny), FuzzyLogic::AND(m_Medium, m_Small));
	m_mediumVal = FuzzyLogic::AND(m_Close, m_Tiny);
	m_highVal = FuzzyLogic::AND(m_Close, FuzzyLogic::NOT(m_Medium));

	//Defuzzification
	return (m_lowVal * 10 + m_mediumVal * 30 + m_highVal * 50) / (m_lowVal + m_mediumVal + m_highVal);
}
