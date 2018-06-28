#include "CImg.h"
#include "kf/kf_vector.h"
#include "scene.h"
#include "renderable.h"
#include "kf/kf_ray.h"
#include "light.h"
#include "windows.h"
#include "lua/lua.hpp"
#include "luascript.h"
#include "main.h"

using namespace cimg_library;

int l_progressive(lua_State *L)
{
	if (lua_gettop(L) > 0)
	{
		progressiveCount = lua_tointeger(L, 1);
		progressiveDisplay = true;
	}
	return 0;
}

int l_resolution(lua_State *L)
{
	if (lua_gettop(L) > 1)
	{
		windowWidth = lua_tointeger(L, 1);
		windowHeight = lua_tointeger(L, 2);
	}
	return 0;
}

int l_camera(lua_State *L)
{
	if (lua_gettop(L) > 0)
	{
		lua_getfield(L, 1, "fov");
		if (lua_isnumber(L, -1))
		{
			g_scene.m_camera.m_fov = (float)lua_tonumber(L, -1);
			g_scene.m_camera.m_orthographic = false;
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "pos");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			g_scene.m_camera.m_position.x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			g_scene.m_camera.m_position.y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			g_scene.m_camera.m_position.z = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "lookat");
		if (lua_istable(L, -1))
		{
			kf::Vector3 look(0, 0, 0);
			lua_rawgeti(L, -1, 1);
			look.x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			look.y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			look.z = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			g_scene.m_camera.lookAt(look);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "ortho");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			g_scene.m_camera.m_orthoSize.x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			g_scene.m_camera.m_orthoSize.y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			g_scene.m_camera.m_orthographic = true;
		}
		lua_pop(L, 1);

	}
	return 0;
}

int l_sphere(lua_State *L)
{
	Sphere *s = new Sphere;

	if (lua_gettop(L) > 0)
	{
		lua_getfield(L, 1, "radius");
		if (lua_isnumber(L, -1))
		{
			s->m_radius = (float)lua_tonumber(L, -1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "pos");
		if (lua_istable(L,-1))
		{
			lua_rawgeti(L, -1, 1);
			s->m_position.x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			s->m_position.y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			s->m_position.z = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "diffuse");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			s->m_material.m_diffuse.r = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			s->m_material.m_diffuse.g = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			s->m_material.m_diffuse.b = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "specular");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			s->m_material.m_specular.r = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			s->m_material.m_specular.g = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			s->m_material.m_specular.b = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "reflective");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			s->m_material.m_reflective.r = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			s->m_material.m_reflective.g = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			s->m_material.m_reflective.b = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "power");
		if (lua_isnumber(L, -1))
		{
			s->m_material.m_specularPower = (float)lua_tonumber(L, -1);
		}
		lua_pop(L, 1);
	}
	g_scene.m_renderables.push_back(s);

	return 0;
}

int l_light(lua_State *L)
{
	Light *light = new Light;

	if (lua_gettop(L) > 0)
	{
		lua_getfield(L, 1, "pos");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			light->m_position.x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			light->m_position.y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			light->m_position.z = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 1, "colour");
		if (lua_istable(L, -1))
		{
			lua_rawgeti(L, -1, 1);
			light->m_colour.r = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			light->m_colour.g = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);
			light->m_colour.b = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);
	}
	g_scene.m_lights.push_back(light);

	return 0;
}

int l_skybox(lua_State *L)
{
	if (lua_gettop(L) > 0)
	{
		std::string name = lua_tostring(L, 1);
		g_scene.m_skytexture.load_bmp(name.c_str());
	}
	return 0;
}

int l_sky(lua_State *L)
{
	if (lua_gettop(L) > 2)
	{
		g_scene.m_sky.r = (float)lua_tonumber(L, 1);
		g_scene.m_sky.g = (float)lua_tonumber(L, 2);
		g_scene.m_sky.b = (float)lua_tonumber(L, 3);
	}
	return 0;
}

int l_ambient(lua_State *L)
{
	if (lua_gettop(L) > 2)
	{
		g_scene.m_ambient.r = (float)lua_tonumber(L, 1);
		g_scene.m_ambient.g = (float)lua_tonumber(L, 2);
		g_scene.m_ambient.b = (float)lua_tonumber(L, 3);
	}
	return 0;
}

int l_shadows(lua_State *L)
{
	if (lua_gettop(L) > 0)
	{
		g_scene.m_shadows = lua_toboolean(L, 1);
	}
	return 0;
}

int l_recursiveLimit(lua_State *L)
{
	if (lua_gettop(L) > 0)
	{
		g_scene.m_recurseLimit = lua_tointeger(L, 1);
	}
	return 0;
}


int l_message(lua_State *L)
{
	if (lua_gettop(L)>0)
		MessageBox(0, lua_tostring(L, -1), "Lua sript error", 0);
	return 0;
}

void initLua(std::string filename)
{
	g_state = luaL_newstate();
	luaL_openlibs(g_state);
	lua_register(g_state, "resolution", l_resolution);
	lua_register(g_state, "sphere", l_sphere);
	lua_register(g_state, "light", l_light);
	lua_register(g_state, "progressive", l_progressive);
	lua_register(g_state, "sky", l_sky);
	lua_register(g_state, "skybox", l_skybox);
	lua_register(g_state, "recursiveLimit", l_recursiveLimit);
	lua_register(g_state, "shadows", l_shadows);
	lua_register(g_state, "ambient", l_ambient);
	lua_register(g_state, "camera", l_camera);

	int result;
	result = luaL_loadfile(g_state, filename.c_str());
	if (result==0)
	{
		result = lua_pcall(g_state, 0, LUA_MULTRET, 0);
		if (result)
		{
			l_message(g_state);
		}
	}
	else
	{
		l_message(g_state);
	}
}
