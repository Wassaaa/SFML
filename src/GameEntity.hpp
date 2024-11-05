#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP
# include <iostream>
# include <SFML/Graphics.hpp>
# include <memory>
# include <vector>
# include <cstdlib>
# include <cmath>
# include "Sprite2DComponent.hpp"

class GameEntity
{
public:
	GameEntity(const std::string name);
	~GameEntity();

	void setPosition(float x, float y);

	void addSpriteComponent2D(std::string filepath);

	void autoMove();
	void render(sf::RenderWindow& ref);

private:
	const std::string name;
	std::vector<std::shared_ptr<IComponent>> components;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	float speed;
	sf::Vector2f spriteSize;

	void checkBounds(sf::Vector2u windowSize);

	void initVariables();
};

#endif
