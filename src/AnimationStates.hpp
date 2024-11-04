#ifndef ANIMATION_STATES_HPP
# define ANIMATION_STATES_HPP

typedef enum e_anim_state {
	NOTHING,
	IDLE,
	JUMPING,
	FALLING,
	WALKING
} t_anim_state;

typedef enum e_mv_dir {
	MV_RIGHT,
	MV_LEFT
} t_mv_dir;

#endif
