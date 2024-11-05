#ifndef SPRITE2DCOMPONENT_HPP
# define SPRITE2DCOMPONENT_HPP
# include <SFML/Graphics.hpp>
# include "IComponent.hpp"

class Sprite2DComponent : public IComponent
{
	public:
		Sprite2DComponent(const std::string filepath);
		~Sprite2DComponent();
		void render(sf::RenderWindow& ref);
		void setPosition(float x, float y);

		sf::Sprite& getSprite() { return this->sprite; }

	private:
		sf::Texture	texture;
		sf::Sprite	sprite;
};

#endif
