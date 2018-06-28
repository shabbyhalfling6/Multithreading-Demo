#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "renderable.h"
#include "kf/kf_vector.h"
#include "kf/kf_ray.h"
#include "light.h"
#include "camera.h"
#include "CImg.h"

/*
	Scene is the primary class for managing the ray trace. 
	It performs the actual trace, shadow checks and maintains 
	the camera and the collections of renderable objects and lights.
*/
class Scene
{
public:
	Scene();
	~Scene();

	// Test for intersect of a ray against all renderable objects.
	// ray - the ray being tested.
	// return - a HitPoint describing the intersect point (if one exists).
	HitPoint intersect(const kf::Ray &ray);
	
	// Trace a ray into the scene through camera coordinates.
	// Camera coordinates vary depending on the projection mode (spherical perspective or orthographic).
	// x - camera coordinates in the range -1 to 1 (left to right)
	// y - camera coordinates in the range 1 to -1 (top to bottom)
	// return - the calculated colour at that camera coordinate.
	kf::Colour trace(float x, float y);

	// Trace a ray into the scene through a ray.
	// ray - the ray being tested.
	// recurseDepth - current depth of recursion. If trace is called with a recurseDepth equal to m_recurseLimit the function stops recursion and returns black.
	// return - the calculated colour the ray is looking at.
	kf::Colour trace(const kf::Ray &ray, int recurseDepth);

	std::vector<Renderable *> m_renderables;	// All renderable objects in the scene.
	std::vector<Light *> m_lights;				// All lights in the scene.
	kf::Colour m_ambient;						// Ambient light value.
	kf::Colour m_sky;							// The sky colour (not currently used).
	Camera m_camera;							// The camera.
	bool m_shadows;								// True if shadows should be rendered.
	int m_recurseLimit;							// How many times a ray can be reflected recursively.
	cimg_library::CImg<float> m_skytexture;		// A texture file loaded as the skybox. It should be in 360x180 degree spherical projection.
};



#endif
