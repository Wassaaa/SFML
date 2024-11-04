#ifndef ANIM_HPP
# define ANIM_HPP
# include "../pch.hpp"

class Anim
{
public:
	Anim();
	Anim(sf::Time frameDuration, bool loop = true);
	~Anim();

	//functions
	void addFrame(const sf::IntRect &frame);
	bool update(float dt);

	//setters
	void play() { this->isPlaying = true; }
	void pause() { this->isPlaying = false; }
	void stop() { this->isPlaying = false; currentFrame = 0; currentTime = sf::Time::Zero; }

	//getters
	const sf::IntRect getCurrentFrame() const { return frames[currentFrame]; }

private:
	std::vector<sf::IntRect>	frames;
	sf::Time					frameDuration;
	sf::Time					currentTime;
	size_t						currentFrame;
	bool						isLooping;
	bool						isPlaying;
};

#endif
