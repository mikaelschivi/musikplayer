#pragma once

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <ostream>

#include "libvlc.h"

#define WINDOW_W 640
#define WINDOW_H 360

class Imgui
{
private:

public:
    SDL_WindowFlags window_flags;
    SDL_Window* window;
    SDL_GLContext gl_context;

    int run();
    void Cleanup(SDL_Window* w, SDL_GLContext gl);
};