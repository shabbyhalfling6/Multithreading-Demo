////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_STREAMS_HEADER
#define KF_STREAMS_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <ostream>

inline std::ostream &operator<<(std::ostream &o, const kf::Vector2f &v)
{
	o << "<" << v.x << ", " << v.y << ">";
	return o;
}

inline std::ostream &operator<<(std::ostream &o, const kf::Vector3f &v)
{
	o << "<" << v.x << ", " << v.y << ", " << v.z << ">";
	return o;
}

inline std::ostream &operator<<(std::ostream &o, const kf::Vector4f &v)
{
	o << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
	return o;
}

#endif
