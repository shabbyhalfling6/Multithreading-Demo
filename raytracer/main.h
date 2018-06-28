#ifndef MAIN_H
#define MAIN_H
#include "scene.h"
#include "lua/lua.hpp"

// This controls if the rendering displays progressively. When timing the results, turn this off (otherwise updating the window repeatedly will affect the timing)
// progressiveCount is how many lines are rendered before updating the window.
extern bool progressiveDisplay;
extern int  progressiveCount;

// The resolution of the window and the output of the ray tracer. This can be overridden by the Lua startup script.
extern int windowWidth;
extern int windowHeight;

// The scene object.
extern Scene g_scene;

// Lua state object used to run the startup script.
extern lua_State *g_state;

#endif
