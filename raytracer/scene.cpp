#include "scene.h"
#include "kf/kf_algorithms.h"

Scene::Scene() :m_ambient(0.0f, 0.0f, 0.0f), m_sky(0.1f, 0.3f, 0.8f), m_shadows(true), m_recurseLimit(4)
{
//	m_skytexture.load_bmp("KKZ5V.bmp");
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < m_lights.size(); ++i)
	{
		delete m_lights[i];
	}
	for (unsigned int i = 0; i < m_renderables.size(); ++i)
	{
		delete m_renderables[i];
	}
}

HitPoint Scene::intersect(const kf::Ray &ray)
{
	HitPoint hp;

	for (unsigned int i = 0; i < m_renderables.size(); ++i)
	{
		if (m_renderables[i]->m_active)
		{
			// Find the nearest intersect point.
			hp.nearest(m_renderables[i]->intersect(ray));
		}
	}
	return hp;
}

kf::Colour Scene::trace(float x, float y)
{
	kf::Colour output;
	kf::Ray ray = m_camera.viewToRay(x, y);
	output = trace(ray, 0);

	return output;
}

kf::Colour Scene::trace(const kf::Ray &ray, int recurseDepth)
{
	kf::Colour output = m_sky;

	if (recurseDepth > m_recurseLimit)
	{
		output.set(0, 0, 0);
		return output;
	}

	if (!m_skytexture.is_empty())
	{
		// Get the colour of the skybox that this ray would hit.
		int tx = int(kf::remap<float>(-3.14159265f, 3.14159265f, 0, m_skytexture.width() - 1.0f, atan2(ray.delta().x, ray.delta().z)));
		int ty = int(kf::remap<float>(1.0f, -1.0f, 0, m_skytexture.height() - 1.0f, ray.delta().y));
		output.r = *m_skytexture.data(tx, ty, 0, 0) / 255.0f;
		output.g = *m_skytexture.data(tx, ty, 0, 1) / 255.0f;
		output.b = *m_skytexture.data(tx, ty, 0, 2) / 255.0f;
		output.toLinear();
	}

	// Find the intersect with the scene.
	HitPoint hp = intersect(ray);
	// If true, we hit something. Otherwise return the skybox.
	if (hp.m_hit)
	{
		kf::Colour specColour(0, 0, 0);
		kf::Colour diffuseColour(0, 0, 0);

		// Loop through every light in the scene.
		for (unsigned int i = 0; i < m_lights.size(); ++i)
		{
			// Direction and distance from the intersect point to the current light.
			kf::Vector3 lightDirection = m_lights[i]->m_position - hp.m_position;
			float lightDistance = lightDirection.normalise();

			kf::Colour lightColour = m_lights[i]->m_colour;
			if (m_shadows)
			{
				// Cast a ray from the intersect point to each light. If anything is in the way, a shadow is being cast on the intersect point.
				kf::Ray shadowRay;
				shadowRay.start(hp.m_position + lightDirection*0.001f); // The lightDirection*0.001f bit is to stop floating point error making the ray collide with it's starting point.
				shadowRay.delta(lightDirection);
				HitPoint shadowhp = intersect(shadowRay);

				// If a shadow is detected, the light's contribution is zero.
				if (shadowhp.m_hit && shadowhp.m_distance < lightDistance)
				{
					lightColour.set(0, 0, 0);
				}
			}

			// Calculate standard lambert diffuse lighting
			float lambert = hp.m_normal.dot(lightDirection);
			if (lambert < 0)
				lambert = 0;

			// Accumulate diffuse lighting.
			diffuseColour = diffuseColour + hp.m_renderable->m_material.m_diffuse * lightColour * lambert;

			// Accumulate specular lighting.
			kf::Vector3 rl = lightDirection.reflect(hp.m_normal);
			float specular = rl.dot(ray.delta());
			if (specular > 0)
			{
				specColour += hp.m_renderable->m_material.m_specular * m_lights[i]->m_colour * pow(specular, hp.m_renderable->m_material.m_specularPower);
			}
		}

		kf::Colour reflectionColour(0,0,0);
		kf::Ray reflectionRay;
		// If the hit object's material has reflection, cast a new ray recursively.
		if (hp.m_renderable->m_material.m_reflective.length() > 0)
		{
			reflectionRay.delta(normalise(ray.delta().reflect(hp.m_normal)));
			reflectionRay.start(hp.m_position + reflectionRay.delta()*0.001f);
			reflectionColour = trace(reflectionRay, recurseDepth + 1) * hp.m_renderable->m_material.m_reflective;
		}

		// Final output is diffuse + specular + reflection.
		output = m_ambient*1 + diffuseColour*1 + specColour*1 + reflectionColour*1;
	}

	return output;
}

