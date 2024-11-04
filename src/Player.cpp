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
	if (this->velocity.x > 0.f)
	{
		this->sprite.setOrigin({0, 0});
		this->sprite.setScale(this->scale, this->scale);
		this->moveDirection = MV_RIGHT;
		animations.playAnimation(WALKING);
	}
	if (this->velocity.x < 0.f)
	{
		this->sprite.setOrigin({this->sprite.getGlobalBounds().width / this->scale, 0});
		this->sprite.setScale(-this->scale, this->scale);
		this->moveDirection = MV_LEFT;
		animations.playAnimation(WALKING);
	}
	if (this->velocity.y > 0.f)
	{
		animations.playAnimation(FALLING);
	}
	if (this->velocity.y < 0.f)
	{
		animations.playAnimation(JUMPING);
	}
	if (this->velocity.x == 0 && this->velocity.y == 0)
	{
		animations.playAnimation(IDLE);
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
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0) ? -1.f : 1.f);
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
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1.f : 1.f);
}

void Player::jump()
{
	if (!this->canjump)
		return;
	this->velocity.y = -50.f;
	this->canjump = false;
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
	this->moveDirection = MV_RIGHT;
	this->canjump = true;
	this->scale = 3.f;
}

void Player::initSprite()
{
	this->sprite.setScale(this->scale, this->scale);
}

void Player::initAnim()
{
	animations.loadTexture("/home/a/SFML/textures/rpg_char/Characters(100x100)/Soldier/Soldier with shadows/Soldier.png");
	animations.addAnim(IDLE, {100, 100}, {0, 0}, 6, sf::Time(sf::milliseconds(100)), true);
	animations.addAnim(WALKING, {100, 100}, {0, 1}, 8, sf::Time(sf::milliseconds(100)), true);
	animations.addAnim(JUMPING, {100, 100}, {0, 2}, 6, sf::Time(sf::milliseconds(50)), false);
	animations.addAnim(FALLING, {100, 100}, {0, 3}, 6, sf::Time(sf::milliseconds(50)), false);
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.92f;
	this->gravity = 4.f;
	this->velocityMaxY = 45.f;
	// this->velocity = sf::Vector2f(0.f, 0.f);
}
