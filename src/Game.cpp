#include "Game.hpp"

Game::Game()
{
	this->initWindow();
	this->initInput();
	this->initTileSheet();
	this->initTileMap();
	this->initPlayer();
}

Game::~Game()
{
}

const sf::RenderWindow &Game::getWindow() const
{
	return (this->window);
}

void Game::updateInput()
{
	//Update Mouse Positions
	int x = int(sf::Mouse::getPosition(this->window).x);
	int y = int(sf::Mouse::getPosition(this->window).y);
	int tile_size = int(this->tileMap.get()->getTileSize());
	std::cout << x << " : " << y << "( " << x / tile_size << " : " << y / tile_size << " )" << std::endl;

	int rand_x = rand() % this->tilesWidth;
	int rand_y = rand() % this->tilesHeight;
	sf::IntRect random_rect = sf::IntRect(rand_x * this->tileSize, rand_y * this->tileSize, this->tileSize, this->tileSize);

	//player movement
	if (sf::Keyboard::isKeyPressed(this->keyboardMappings["MOVE_LEFT"]))
		this->player.get()->move(-1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(this->keyboardMappings["MOVE_RIGHT"]))
		this->player.get()->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(this->keyboardMappings["JUMP"]))
		this->player.get()->jump();
	//tile functions
	if (sf::Mouse::isButtonPressed(this->mouseMappings["BTN_ADD_TILE"]))
		this->tileMap.get()->addTile(x / tile_size, y / tile_size, this->tileScale, random_rect);
	else if (sf::Mouse::isButtonPressed(this->mouseMappings["BTN_REMOVE_TILE"]))
		this->tileMap.get()->removeTile(x / tile_size, y / tile_size);
}

void Game::update()
{
	this->deltaTime = deltaClock.restart().asSeconds();
	while (this->window.pollEvent(this->ev))
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window.close();
			break ;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window.close();
			break ;
		default:
			break ;
		}
	this->updateInput();
	this->updatePlayer();
	this->updateCollision();
	this->updateTileMap();
}

void Game::render()
{
	this->window.clear();
	// render game
	this->renderTileMap();
	this->renderPlayer();
	this->window.display();
}

void Game::renderPlayer()
{
	this->player.get()->render(this->window);
}

void Game::renderTileMap()
{
	this->tileMap.get()->render(this->window);
}

void Game::updatePlayer()
{
	this->player.get()->update(dt());
}

void Game::updateCollision()
{
	sf::Vector2f pos = this->player.get()->getPosition();
	sf::FloatRect bounds = this->player.get()->getGlobalBounds();
	if (pos.y + bounds.height >= this->window.getSize().y)
	{
		this->player.get()->resetVelocityY();
		this->player.get()->setPosition(pos.x, this->window.getSize().y
			- bounds.height);
	}
}

void Game::updateTileMap()
{
	this->tileMap.get()->update();
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Game Plat");
	this->window.setFramerateLimit(60);
}

void Game::initInput()
{
	this->mouseMappings["BTN_ADD_TILE"] = sf::Mouse::Button::Left;
	this->mouseMappings["BTN_REMOVE_TILE"] = sf::Mouse::Button::Right;
	this->keyboardMappings["MOVE_LEFT"] = sf::Keyboard::Key::A;
	this->keyboardMappings["MOVE_RIGHT"] = sf::Keyboard::Key::D;
	this->keyboardMappings["JUMP"] = sf::Keyboard::Key::W;
}

void Game::initPlayer()
{
	this->player = std::make_shared<Player>();
}

void Game::initTileSheet()
{
	if (!this->tileSheet.loadFromFile("../../textures/Legacy/Assets/Packs/grotto_escape_pack/Base pack/Spritesheets/tiles.png"))
		std::cout << "tiles map error";
	this->tileScale = 4.f;
	this->tileSize = 16;
	this->tilesWidth = this->tileSheet.getSize().x / this->tileSize;
	this->tilesHeight = this->tileSheet.getSize().y / this->tileSize;
}

void Game::initTileMap()
{
	sf::Vector2u size = this->window.getSize();

	this->tileMap = std::make_shared<TileMap>(size.x, size.y, &this->tileSheet, int(this->tileSize * this->tileScale));
}
