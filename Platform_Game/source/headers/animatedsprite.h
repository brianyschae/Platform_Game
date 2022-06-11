#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>
#include <vector>
#include "sprite.h"
#include "globals.h"

// Holds logic for animating sprites

class Graphics;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
		float poX, float posY, float timeToUpdate);

	// Plays the animation provided
	void playAnimation(std::string animation, bool once = false);

	// Updates the animated sprite
	void update(int elapsedTime);

	// Draws the sprite to the screen
	void draw(Graphics &graphics, int x, int y);

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;
	

	// Adds and animation to the map of animation for the sprite
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	// Resets all animations associated with this sprite
	void resetAnimation();

	// Stops the current animation
	void stopAnimation();

	// Changes the visibility of the animated sprite
	void setVisible(bool visible);

	// Logic that happens when an animation ends
	virtual void animationDone(std::string currentAnimation) = 0;

	// A required function that sets up animations
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};

#endif
