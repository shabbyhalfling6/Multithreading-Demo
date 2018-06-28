#ifndef LIGHT_H
#define LIGHT_H

#include "kf/kf_vector.h"
#include "kf/kf_ray.h"


class Light
{
public:
	kf::Vector3 m_position;
	kf::Colour m_colour;
};



#endif
