#include "GameEntity.hpp"

GameEntity::GameEntity(const std::string name) : name(name)
{
	float	x;
	float	y;
	float	len;

	this->initVariables();
	x = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
	y = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
	len = std::sqrt(x * x + y * y);
	if (len == 0)
		len = 1.f;
	this->velocity.x = x / len * speed;
	this->velocity.y = y / len * speed;
}

GameEntity::~GameEntity()
{
}

void GameEntity::setPosition(float x, float y)
{
	this->pos = sf::Vector2f(x, y);
	for (auto &component : this->components)
	{
		component->setPosition(x, y);
	}
}

void GameEntity::addSpriteComponent2D(std::string filepath)
{
	auto component = std::make_shared<Sprite2DComponent>(filepath);
	this->components.emplace_back(component);
	this->spriteSize = sf::Vector2f(
							component->getSprite().getGlobalBounds().width,
							component->getSprite().getGlobalBounds().height
	);
}

void GameEntity::render(sf::RenderWindow &ref)
{
	this->checkBounds(ref.getSize());
	this->autoMove();

	for (auto &component : this->components)
	{
		component->setPosition(this->pos.x, this->pos.y);
		component->render(ref);
	}
}

void GameEntity::autoMove()
{
	this->pos += this->velocity;
}

void GameEntity::checkBounds(sf::Vector2u windowSize)
{
	if (this->pos.x <= 0)
	{
		this->pos.x = 0;
		velocity.x *= -1;
	}
	else if (this->pos.x + this->spriteSize.x >= windowSize.x)
	{
		this->pos.x = windowSize.x - this->spriteSize.x;
		velocity.x *= -1;
	}
	if (this->pos.y <= 0)
	{
		this->pos.y = 0;
		velocity.y *= -1;
	}
	else if (this->pos.y + this->spriteSize.y >= windowSize.y)
	{
		this->pos.y = windowSize.y - this->spriteSize.y;
		velocity.y *= -1;
	}
}

void GameEntity::initVariables()
{
	this->speed = 5.f;
}
