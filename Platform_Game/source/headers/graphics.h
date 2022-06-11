#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include <map>
#include <string>

// Holds all information dealing wiht graphics for the game

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    // Loads an image into the _spriteSheets map if it doesn't already exist
    SDL_Surface* loadImage(const std::string &filePath);

    // Draws a texture
    void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

    // Renders everything
    void flip();

    // Clears the screen
    void clear();

    // Returns the renderer
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif