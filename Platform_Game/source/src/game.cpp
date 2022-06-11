#include "SDL.h"

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    this->_level = Level("Map 1", Vector2(100, 100), graphics);
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint());

    int START_TIME = SDL_GetTicks();

    while (true) {
        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.repeat == 0) {
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP) {
                input.keyUpEvent(event);
            }
            // Quit if window is closed
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        // Quit if esc is pressed
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
            return;
        }
        else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
            this->_player.moveLeft();
        }
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
            this->_player.moveRight();
        }

        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            this->_player.stopMoving();
        }

        const int CURRENT_TIME = SDL_GetTicks();

        // Limitinng fps so that player physics is the same on all computers
        int ELAPSED_TIME = CURRENT_TIME - START_TIME;
        this->update((float) std::min(ELAPSED_TIME, MAX_FRAME_TIME));
        START_TIME = CURRENT_TIME;

        // Draws the rendered graphics
        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

    this->_level.draw(graphics);
    this->_player.draw(graphics);

    graphics.flip();
}

void Game::update(float elapsedTime) {
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime);

    //Check collisions
    std::vector<Rectangle> others;
    if ((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0) {
        //Player collided with at least one tile. Handle it.
        this->_player.handleTileCollisions(others);
    }
}
