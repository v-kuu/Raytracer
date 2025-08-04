#pragma once

// Classes
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

// Utils

///////////////////////////////////////////////////////// initialize_sdl.cpp //
Texture	*initialize_sdl(void);

///////////////////////////////////////////////////////// run_event_loop.cpp //
void	run_event_loop(Texture *canvas);
