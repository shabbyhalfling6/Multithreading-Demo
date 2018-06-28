#include "renderable.h"
#include <algorithm>

void HitPoint::nearest(const HitPoint &hp)
{
	if (!m_hit)
		*this = hp;
	else
	{
		if (hp.m_hit && hp.m_distance < m_distance)
		{
			*this = hp;
		}
	}
}

Renderable::Renderable() :m_active(true)
{
}

Sphere::Sphere(float rad) :m_radius(rad)
{
}

HitPoint Sphere::intersect(const kf::Ray &ray)
{
	HitPoint hp;
	kf::Vector3 L = m_position-(ray.start());

	float tca = L.dot(ray.delta()); 
	if (tca < 0) return hp; 
	float d2 = L.dot(L) - tca * tca; 
	if (d2 > m_radius*m_radius) return hp; 
	float thc = sqrt(m_radius*m_radius - d2);
	float t0 = tca - thc; 
	float t1 = tca + thc;
	float m = std::min(t0, t1);
	hp.m_hit = true;
	hp.m_position = ray.interpolate(m);
	hp.m_renderable = this;
	hp.m_normal = normalise(hp.m_position-m_position);
	hp.m_distance = m;

	return hp;
}

