#ifndef ANIMCOMPONENT_HPP
# define ANIMCOMPONENT_HPP
# include "../pch.hpp"
# include "Anim.hpp"
# include "AnimationStates.hpp"

class AnimComponent
{
public:
	AnimComponent(sf::Sprite &sprite);
	~AnimComponent();

	bool loadTexture(const std::string& texturePath);
	void addAnim(const PlayerState animState, const sf::Vector2i& frameSize,
				const sf::Vector2i& startPos, size_t frames, sf::Time frameDuration,
				bool loop);
	void playAnimation(PlayerState anim);
	void update(float dt);


private:
	sf::Sprite&								sprite;
	sf::Texture								animSheet;
	std::unordered_map<PlayerState, Anim>	animations;
	PlayerState								currentAnimation;
};

#endif
