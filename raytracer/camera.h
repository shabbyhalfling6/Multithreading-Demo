#ifndef CAMERA_H
#define CAMERA_H

#include "kf/kf_vector.h"
#include "kf/kf_ray.h"


class Camera
{
public:
	kf::Vector3 m_position;
	kf::Vector3 m_forward;
	kf::Vector3 m_right;
	kf::Vector3 m_up;
	bool m_orthographic;
	kf::Vector2 m_orthoSize;
	float m_fov;
	
	Camera();
	kf::Ray viewToRay(float x, float y) const;
	void lookAt(const kf::Vector3 &target);

};



#endif
