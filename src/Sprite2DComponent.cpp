#include "Sprite2DComponent.hpp"

Sprite2DComponent::Sprite2DComponent(const std::string filepath)
{
	texture.loadFromFile(filepath);
	sprite.setTexture(texture);
	sprite.setOrigin(.5f, .5f);
}

Sprite2DComponent::~Sprite2DComponent()
{
}

void Sprite2DComponent::render(sf::RenderWindow &ref)
{
	ref.draw(sprite);
}

void Sprite2DComponent::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}
