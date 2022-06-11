#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include <map>

// Keeps track of keyboard state

class Input {
public:
    // This function get called at the beginning of each new frame to reset the keys that are no longer relevant
    void beginNewFrame();
    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event& event);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
};

#endif