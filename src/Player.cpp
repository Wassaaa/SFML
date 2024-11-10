#include "Player.hpp"

Player::Player() : animations(sprite)
{
	this->initVariables();
	this->initSprite();
	this->initAnim();
	this->initPhysics();
}

Player::~Player()
{
}

void Player::update(float &dt)
{
	this->updateMovement();
	this->updatePhysics();
	this->updateAnim(dt);
}

void Player::render(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}

void Player::updateMovement()
{
	PlayerState newState = this->determineState();
	this->updateSpriteFacing();
	if (newState != currentState)
	{
		currentState = newState;
		switch (currentState)
		{
		case PlayerState::IDLE:
			animations.playAnimation(PlayerState::IDLE);
			break;
		case PlayerState::WALKING:
			animations.playAnimation(PlayerState::WALKING);
			break;
		case PlayerState::JUMPING:
			animations.playAnimation(PlayerState::JUMPING);
			break;
		case PlayerState::FALLING:
			animations.playAnimation(PlayerState::FALLING);
			break;

		default:
			break;
		}
	}
}

void Player::updateAnim(float &dt)
{
	animations.update(dt);
}

void Player::updatePhysics()
{
	// gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0) ?
				-1.f : 1.f);
	// limit gravity
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;
	// deceleration
	this->velocity *= this->drag;
	// limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{
	// acceleration
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += dir_y * this->acceleration;
	// limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ?
				-1.f : 1.f);
}

void Player::jump()
{
	if (!this->canjump)
		return ;
	this->velocity.y = -50.f;
	this->canjump = false;
}

void Player::updateSpriteFacing()
{
	if (velocity.x > 0.f)
	{
		this->sprite.setOrigin({0, 0});
		this->sprite.setScale(this->scale, this->scale);
	}
	else if (velocity.x < 0.f)
	{
		this->sprite.setOrigin({this->sprite.getGlobalBounds().width / this->scale, 0});
		this->sprite.setScale(-this->scale, this->scale);
	}
}

PlayerState Player::determineState()
{
	if (this->velocity.y < 0.f)
		return PlayerState::JUMPING;
	if (this->velocity.y > 0.f)
		return PlayerState::FALLING;
	if (velocity.x != 0.f)
		return PlayerState::WALKING;
	return PlayerState::IDLE;
}

const sf::Vector2f Player::getPosition() const
{
	return (this->sprite.getPosition());
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return (this->sprite.getGlobalBounds());
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
	this->canjump = true;
}

void Player::initVariables()
{
	this->moveDirection = MoveDir::RIGHT;
	this->currentState = PlayerState::IDLE;
	this->canjump = true;
	this->scale = 3.f;
}

void Player::initSprite()
{
	this->sprite.setScale(this->scale, this->scale);
}

void Player::initAnim()
{
	if (!animations.loadTexture("../../textures/rpg_char/Characters(100x100)/Soldier/Soldier with shadows/Soldier.png"))
		std::cout << "ERROR::PLAYER::INIT_ANIM::LOAD_TEXTURE\n";
	animations.addAnim(PlayerState::IDLE, {100, 100}, {0, 0}, 6,
		sf::Time(sf::milliseconds(100)), true);
	animations.addAnim(PlayerState::WALKING, {100, 100}, {0, 1}, 8,
		sf::Time(sf::milliseconds(100)), true);
	animations.addAnim(PlayerState::JUMPING, {100, 100}, {0, 2}, 6,
		sf::Time(sf::milliseconds(50)), false);
	animations.addAnim(PlayerState::FALLING, {100, 100}, {0, 3}, 6,
		sf::Time(sf::milliseconds(50)), false);
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.92f;
	this->gravity = 2.f;
	this->velocityMaxY = 45.f;
}
