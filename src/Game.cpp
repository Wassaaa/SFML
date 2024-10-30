#include "Game.hpp"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

// copy constructor
Game::Game(const Game &other)
{
}

// copy assignment op
Game &Game::operator=(const Game &other)
{
	if (this == &other)
		return (*this);
	// stupid warning fix :D
	return (*this);
}

Game::~Game()
{
	delete this->window;
}

// accessors

const bool Game::running() const
{
	return (this->window->isOpen());
}

// functions
void Game::update()
{
	this->pollEvents();
	if (this->health > 0)
	{
		// this->updateMousePositions();
		this->updateEnemies();
	}
}

void Game::updateEnemies()
{
	bool deleted = false;
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.0f;
		}
		else
			this->enemySpawnTimer += 1.0f;

	}
	for (int i = 0; i < this->enemies.size(); i++)
	{

		if (this->mouseClickPos.x > -1 && this->mouseClickPos.y > -1)
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mouseClickPos))
			{
				this->enemies.erase(this->enemies.begin() + i);
				deleted = true;
				this->mouseClickPos = sf::Vector2f(-1.0f, -1.0f);
				this->points += 10u;
			}
		}
		if (!deleted && this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			deleted = true;
			this->health -= 10;
		}
		if (!deleted)
			this->enemies[i].move(0.f, 2.0f);
	}
	deleted = false;
	this->mouseClickPos = sf::Vector2f(-1.0f, -1.0f);
}

void Game::render()
{
	this->window->clear();
	// render items
	// this->window->draw(this->enemy);
	this->renderEnemies();
	// end frame
	this->window->display();
}

void Game::renderEnemies()
{
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break ;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break ;
		case sf::Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == sf::Mouse::Left)
				this->mouseClickPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);
}

void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 100;
	this->enemySpawnTimerMax = 50.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseClickPos = sf::Vector2f(-1.0f, -1.0f);
}

void Game::initWindow()
{
	this->videoMode.height = 600u;
	this->videoMode.width = 800u;
	this->window = new sf::RenderWindow(this->videoMode, "My Game",
			sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
}
