#pragma once

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <ostream>

#include "libvlc.h"
#include "file.h"

#define WINDOW_W 640
#define WINDOW_H 480

class Gui
{
private:
    
public:
    static SDL_WindowFlags window_flags;
    static SDL_Window* window;
    static SDL_GLContext gl_context;

    static const char* selectedFile;
    
    static int run();

    static void Cleanup(SDL_Window* w, SDL_GLContext gl);
};