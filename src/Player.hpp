#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "../pch.hpp"
# include "AnimComponent.hpp"
# include "AnimationStates.hpp"

class Player
{
public:
	Player();
	~Player();

	//functions
	void update(float &dt);
	void render(sf::RenderTarget& target);
	void updatePhysics();
	void updateMovement();
	void updateAnim(float &dt);
	//movement
	void move(const float dir_x, const float dir_y);
	void jump();
	void updateSpriteFacing();
	PlayerState determineState();
	//accessors
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	void setPosition(const float x, const float y);
	void resetVelocityY();

private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	AnimComponent animations;


	//vars
	float scale;

	//Movement
	MoveDir moveDirection;
	PlayerState currentState;
	//Animation

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
	void initAnim();
	void initPhysics();

};

#endif
