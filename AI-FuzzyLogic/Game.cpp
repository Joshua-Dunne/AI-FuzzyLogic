#include "Game.h"

Game::Game() :	m_window(sf::VideoMode(1200u, 896u), "Fuzzy Logic")
{
	//m_window.setFramerateLimit(60u);
	m_force = static_cast<float>((rand() % 30) + 1); // 1 -> 30
	m_range = static_cast<float>((rand() % 81) + 20); // 0 -> 80 + 10 = 20 -> 100

	m_sizeToSend = getArmySize(m_force, m_range);

	if (!m_bgTex.loadFromFile("./assets/sprites/background.png"))
	{
		std::cerr << "Error loading background" << std::endl;
	}

	m_bg.setTexture(m_bgTex);

	enemyArmy = new Army(sf::Vector2f{ 1225.0f, 348.0f }, static_cast<int>(m_force), m_range * 10.0f, sf::Color::Red);
	enemyArmy->beginMoving();

	playerArmy = new Army(sf::Vector2f{ -75.0f, 348.0f }, static_cast<int>(m_sizeToSend), (m_range * 10.0f) - 100.0f, sf::Color::Blue);
	playerArmy->beginMoving();

	if (!m_font.loadFromFile("./assets/fonts/ariblk.ttf"))
	{
		std::cout << "error loading ariblk font" << std::endl;
	}

	m_information.setFont(m_font);
	m_information.setCharacterSize(32u);

	m_information.setString("Enemy Size: " + std::to_string(static_cast<int>(m_force))
		+ ", Enemy Distance from Base: "
		+ std::to_string(static_cast<int>(m_range))
		+ "\n             Calculated Army to send: " + std::to_string(m_sizeToSend)
		+ "\n\n             Press Enter to Re-roll Stats");
	m_information.setPosition(200.0f, 700.0f);
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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				m_force = static_cast<float>((rand() % 30) + 1); // 1 -> 30
				m_range = static_cast<float>((rand() % 81) + 20); // 0 -> 80 + 10 = 20 -> 100

				m_sizeToSend = getArmySize(m_force, m_range);

				delete(enemyArmy);
				enemyArmy = new Army(sf::Vector2f{ 1225.0f, 384.0f }, static_cast<int>(m_force), m_range * 10.0f, sf::Color::Red);
				enemyArmy->beginMoving();

				delete(playerArmy);
				playerArmy = new Army(sf::Vector2f{ -75.0f, 348.0f }, static_cast<int>(m_sizeToSend), (m_range * 10.0f) - 100.0f, sf::Color::Blue);
				playerArmy->beginMoving();

				m_information.setString("Enemy Size: " + std::to_string(static_cast<int>(m_force))
					+ ", Enemy Distance from Base: "
					+ std::to_string(static_cast<int>(m_range))
					+ "\n             Calculated Army to send: " + std::to_string(m_sizeToSend)
					+ "\n\n             Press Enter to Re-roll Stats");
			}
		}
	}
}

void Game::update(sf::Time& dt)
{
	// Update elements
	if(nullptr != enemyArmy)
		enemyArmy->update(dt);
	if (nullptr != playerArmy)
		playerArmy->update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw elements
	m_window.draw(m_bg);

	// Update elements
	if (nullptr != enemyArmy)
		enemyArmy->render(m_window);
	if (nullptr != playerArmy)
		playerArmy->render(m_window);

	m_window.draw(m_information);

	m_window.display();
}

int Game::getArmySize(float t_force, float t_range)
{
	float m_Tiny = 0.0f, m_Small = 0.0f, m_Moderate = 0.0f, m_Large = 0.0f;
	float m_Close = 0.0f, m_Medium = 0.0f, m_Far = 0.0f;
	float m_lowVal = 0.0f, m_mediumVal = 0.0f, m_highVal = 0.0f;

	// Fuzzy Variables Setup & Fuzzification
	// Force
	m_Tiny = FuzzyLogic::Triangle(t_force, -10.0f, 0.0f, 10.0f);
	m_Small = FuzzyLogic::Trapezoid(t_force, 2.5f, 10.0f, 15.0f, 20.0f);
	m_Moderate = FuzzyLogic::Trapezoid(t_force, 15.0f, 20.0f, 25.0f, 30.0f);
	m_Large = FuzzyLogic::Grade(t_force, 25.0f, 30.0f);

	// Range
	m_Close = FuzzyLogic::Triangle(t_range, -30.0f, 0.0f, 30.0f);
	m_Medium = FuzzyLogic::Trapezoid(t_range, 10.0f, 30.0f, 50.0f, 70.0f);
	m_Far = FuzzyLogic::Grade(t_range, 50.0f, 120.0f);

	// Rules Matrix & Application
	// ( Medium AND Tiny ) OR ( Medium AND Small ) OR ( Far AND NOT(Large) )
	m_lowVal = FuzzyLogic::OR(FuzzyLogic::AND(m_Medium, m_Tiny), 
		FuzzyLogic::OR(FuzzyLogic::AND(m_Medium, m_Small), FuzzyLogic::AND(m_Far, FuzzyLogic::NOT(m_Large))));

	// ( Close AND Tiny ) OR ( Medium AND Moderate ) OR ( Far AND Large )
	m_mediumVal = FuzzyLogic::OR(FuzzyLogic::AND(m_Close, m_Tiny),
		FuzzyLogic::OR(FuzzyLogic::AND(m_Medium, m_Moderate), FuzzyLogic::AND(m_Far, m_Large)));

	// ( Close AND NOT(Medium) ) OR ( Medium AND Large )
	m_highVal = FuzzyLogic::OR(FuzzyLogic::AND(m_Close, FuzzyLogic::NOT(m_Medium)), FuzzyLogic::AND(m_Medium, m_Large));

	//Defuzzification
	return static_cast<int>((m_lowVal * 10 + m_mediumVal * 30 + m_highVal * 50) / (m_lowVal + m_mediumVal + m_highVal));
}
