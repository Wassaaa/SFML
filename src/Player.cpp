#include "Player.hpp"

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
}

void Player::update()
{
	this->updateMovement();
	this->updatePhysics();
	this->updateAnimations();
}

void Player::render(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}

void Player::updateMovement()
{
	if (this->velocity.x > 0.f)
		this->animState = MOVING_RIGHT;
	else if (this->velocity.x < 0.f)
		this->animState = MOVING_LEFT;
	else
		this->animState = IDLE;
}

void Player::updateAnimations()
{
	if (this->animationTimer.getElapsedTime().asMilliseconds() >= 100)
	{
		if (this->animState == IDLE)
		{
			this->currentFrame.top = 0;
			this->currentFrame.left += 100;
			if (this->currentFrame.left >= 500)
				this->currentFrame.left = 0;
		}
		else if (this->animState == MOVING_LEFT
			|| this->animState == MOVING_RIGHT)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(this->scale, this->scale);
			this->currentFrame.top = 100;
			this->currentFrame.left += 100;
			if (this->currentFrame.left >= 700)
				this->currentFrame.left = 0;
			if (this->animState == MOVING_LEFT)
			{
				this->sprite.setOrigin(this->sprite.getGlobalBounds().width
					/ this->scale, 0.f);
				this->sprite.setScale(-this->scale, this->scale);
			}
		}
		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
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
	this->velocity.y = -70.f;
	this->canjump = false;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

const bool Player::getAnimSwitch()
{
	if (this->animationSwitch)
	{
		this->animationSwitch = false;
		return (true);
	}
	return (false);
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
}

void Player::initVariables()
{
	this->animState = IDLE;
	this->canjump = true;
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 300, 100, 100);
	this->sprite.setTextureRect(this->currentFrame);
	// this->sprite.setOrigin(sf::Vector2f(50.f, 50.f));
	this->scale = 3.f;
	this->sprite.setScale(this->scale, this->scale);
	this->sprite.move(sf::Vector2f(100.f, 200.f));
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("/home/a/SFML/textures/rpg_char/Characters(100x100)/Soldier/Soldier with shadows/Soldier.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!\n";
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.92f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
	// this->velocity = sf::Vector2f(0.f, 0.f);
}
