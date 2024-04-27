#pragma once

#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_sdl2.h"
#include "./imgui/backends/imgui_impl_opengl2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <ostream>

#define WINDOW_W 640
#define WINDOW_H 360

class Imgui
{
public:
    int fuck_you;
    int runImgui();
};