#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "../pch.hpp"

enum PLAYER_ANIMATION_STATES{
	IDLE,
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	FALLING,
};

class Player
{
public:
	Player();
	~Player();

	//functions
	void update();
	void render(sf::RenderTarget& target);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void move(const float dir_x, const float dir_y);
	void jump();
	void resetAnimationTimer();

	//accessors
	const bool getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	void setPosition(const float x, const float y);
	void resetVelocityY();

private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	//vars
	float scale;

	//Movement

	//Animation
	sf::IntRect currentFrame;
	sf::IntRect def;
	sf::IntRect mirror;
	sf::Clock animationTimer;
	short animState;
	bool animationSwitch;

	//physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;
	bool canjump;


	void initVariables();
	void initSprite();
	void initTexture();
	void initAnimations();
	void initPhysics();

};

#endif
