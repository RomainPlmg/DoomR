#pragma once

#include <SDL3/SDL.h>

struct InputState {
    bool forward = false;
    bool backward = false;
    bool strafeLeft = false;
    bool strafeRight = false;
    bool turnLeft = false;
    bool turnRight = false;
};

class Input {
   public:
    InputState poll() const {
        const bool* keys = SDL_GetKeyboardState(nullptr);
        InputState state;
        state.forward = keys[SDL_SCANCODE_W];
        state.backward = keys[SDL_SCANCODE_S];
        state.strafeLeft = keys[SDL_SCANCODE_A];
        state.strafeRight = keys[SDL_SCANCODE_D];
        state.turnLeft = keys[SDL_SCANCODE_LEFT];
        state.turnRight = keys[SDL_SCANCODE_RIGHT];
        return state;
    }
};