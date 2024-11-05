#ifndef ICOMPONENT_HPP
# define ICOMPONENT_HPP
# include <SFML/Graphics.hpp>

class	IComponent{
	public:
		virtual ~IComponent();
		virtual void render(sf::RenderWindow& ref);
		virtual void setPosition(float x, float y);
};

#endif
