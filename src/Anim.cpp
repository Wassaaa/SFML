#include "Anim.hpp"

Anim::Anim() :
	frameDuration(sf::Time::Zero),
	currentTime(sf::Time::Zero),
	currentFrame(0),
	isLooping(true),
	isPlaying(false)
{
}

Anim::Anim(sf::Time frameDuration, bool loop) : frameDuration(frameDuration),
	currentTime(sf::Time::Zero), currentFrame(0), isLooping(loop),
	isPlaying(false)
{
}

Anim::~Anim()
{
}

void Anim::addFrame(const sf::IntRect &frame)
{
	frames.push_back(frame);
}

bool Anim::update(float dt)
{
	if (!isPlaying)
	{
		return (false);
	}
	currentTime += sf::seconds(dt);
	if (currentTime >= frameDuration)
	{
		currentTime = sf::Time::Zero;
		if (currentFrame + 1 < frames.size())
		{
			++currentFrame;
			return (true);
		}
		else if (isLooping)
		{
			currentFrame = 0;
			return (true);
		}
		else
		{
			isPlaying = false;
			return (false);
		}
	}
	return (false);
}
