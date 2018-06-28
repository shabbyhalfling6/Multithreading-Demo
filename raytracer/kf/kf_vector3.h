////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_VECTOR3_HEADER
#define KF_VECTOR3_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector2.h"

#pragma warning( disable : 4201)

namespace kf
{
	template<typename TT>
	class Vector3T
	{
	public:
		typedef TT type;
		enum
		{
			size = 3
		};
		enum Elements
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1,
			Z = 2, B = 2
		};
		union
		{
			TT e[3];
			union
			{
				struct
				{
					TT x;
					TT y;
					TT z;
				};
				struct
				{
					TT r;
					TT g;
					TT b;
				};
				struct
				{
					TT u;
					TT v;
				};
			};
		};

		inline Vector3T() : x(0), y(0), z(0)
		{
		}

		inline Vector3T(const Vector3T &c) : x(c.x), y(c.y), z(c.z)
		{
		}

		inline Vector3T(const Vector2T<TT> &c, TT f = 0) : x(c.x), y(c.y), z(f)
		{
		}

		inline Vector3T(TT f, const Vector2T<TT> &c) : x(f), y(c.x), z(c.y)
		{
		}

		explicit inline Vector3T(TT xyz) : x(xyz), y(xyz), z(xyz)
		{
		}

		template<typename T2>
		explicit inline Vector3T(const T2 *p) : x(TT(p[0])), y(TT(p[1])), z(TT(p[2]))
		{
		}

		inline Vector3T(TT xx, TT yy, TT zz) : x(xx), y(yy), z(zz)
		{
		}

		inline TT operator [] (unsigned int i) const
		{
			return e[i];
		}

		inline TT& operator [] (unsigned int i)
		{
			return e[i];
		}

		inline Vector3T operator*=(const TT &c)
		{
			x *= c;
			y *= c;
			z *= c;
			return *this;
		}
		inline Vector3T operator/=(const TT &c)
		{
			x /= c;
			y /= c;
			z /= c;
			return *this;
		}
		inline Vector3T operator+=(const Vector3T &c)
		{
			x += c.x;
			y += c.y;
			z += c.z;
			return *this;
		}
		inline Vector3T operator-=(const Vector3T &c)
		{
			x -= c.x;
			y -= c.y;
			z -= c.z;
			return *this;
		}
		inline Vector3T operator*=(const Vector3T &c)
		{
			x *= c.x;
			y *= c.y;
			z *= c.z;
			return *this;
		}
		inline Vector3T operator/=(const Vector3T &c)
		{
			x /= c.x;
			y /= c.y;
			z /= c.z;
			return *this;
		}
		inline Vector3T operator=(const TT *p)
		{
			x = p[0];
			y = p[1];
			z = p[2];
			return *this;
		}
		inline Vector3T operator=(const Vector3T &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		inline float normalise()
		{
			TT l;
			l = TT(sqrt(x*x + y*y + z*z));
			if (l != 0.0)
			{
				set(x / l, y / l, z / l);
			}
			else
			{
				set(0, 0, 0);
			}
			return l;
		}

		inline float normalised()
		{
			Vector3T v(*this);
			v.normalise();
			return v;
		}

		friend inline Vector3T normalise(const Vector3T &v)
		{
			Vector3T temp(v);
			temp.normalise();
			return temp;
		}

		inline TT length() const
		{
			return sqrt(x*x + y*y + z*z);
		}

		friend inline TT length(const Vector3T &v)
		{
			return v.length();
		}

		inline TT lengthSquared() const
		{
			return x*x + y*y + z*z;
		}

		friend inline TT lengthSquared(const Vector3T &v)
		{
			return v.lengthSquared();
		}

		inline void clamp(float low, float high)
		{
			if (x < low) x = low;
			if (x > high) x = high;
			if (y < low) y = low;
			if (y > high) y = high;
			if (z < low) z = low;
			if (z > high) z = high;
		}

		inline Vector3T clamped(float low, float high) const
		{
			Vector3T v(*this);
			v.clamp(low, high);
			return v;
		}

		friend inline TT clamp(const Vector3T &v, float low, float high)
		{
			return v.clamp(low,high);
		}

		inline void clamp(const Vector3T &low, const Vector3T &high)
		{
			if (x < low.x) x = low.x;
			if (x > high.x) x = high.x;
			if (y < low.y) y = low.y;
			if (y > high.y) y = high.y;
			if (z < low.z) z = low.z;
			if (z > high.z) z = high.z;
		}

		inline Vector3T clamped(const Vector3T &low, const Vector3T &high) const
		{
			Vector3T v(*this);
			v.clamp(low, high);
			return v;
		}

		friend inline TT clamp(const Vector3T &v, const Vector3T &low, const Vector3T &high)
		{
			return v.clamp(low, high);
		}

		inline void saturate()
		{
			clamp((TT) 0, (TT) 1);
		}

		inline Vector3T saturated() const
		{
			return clamped((TT)0, (TT)1);
		}

		inline Vector3T up() const
		{
			if (x != 0 || z != 0)
			{
				Vector3T v;
				v = (*this).cross(UNIT_Y()).cross(*this);
				v.normalise();
				return v;
			}
			return Vector3T::UNIT_Z();
		}

		friend inline Vector3T up(const Vector3T &v)
		{
			return v.up();
		}

		inline Vector3T right() const
		{
			if (x != 0 || z != 0)
			{
				Vector3T v;
				v = (*this).cross(UNIT_Y());
				v.normalise();
				return v;
			}
			return Vector3T::UNIT_Z();
		}

		friend inline Vector3T right(const Vector3T &v)
		{
			return v.right();
		}

		inline Vector3T reflect(const Vector3T &n) const
		{
			return *this - (TT)2.0 * n * dot(n);
		}

		friend inline Vector3T reflect(const Vector3T &v, const Vector3T &n)
		{
			return v.reflect(n);
		}

		inline Vector3T dominantAxis() const
		{
			Vector3T v = abs();
			if (v.x >= v.y)
			{
				if (v.x >= v.z)
				{
					return x >= 0 ? UNIT_X() : NEGATIVE_UNIT_X();
				}
				else
				{
					return z >= 0 ? UNIT_Z() : NEGATIVE_UNIT_Z();
				}
			}
			else
			{
				if (v.y >= v.z)
				{
					return y >= 0 ? UNIT_Y() : NEGATIVE_UNIT_Y();
				}
				else
				{
					return z >= 0 ? UNIT_Z() : NEGATIVE_UNIT_Z();
				}
			}
		}

		friend inline Vector3T dominantAxis(const Vector3T &v)
		{
			return v.dominantAxis();
		}

		inline Vector3T swiz(Elements comp1, Elements comp2, Elements comp3) const
		{
			return Vector3T(e[comp1], e[comp2], e[comp3]);
		}

		friend inline Vector3T swiz(const Vector3T &v, Elements comp1, Elements comp2, Elements comp3)
		{
			return v.swiz(comp1,comp2,comp3);
		}

		inline void set(const Vector3T &value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
		}
		
		inline void set(TT xyz)
		{
			x = y = z = xyz;
		}
		
		inline void set(TT xx, TT yy, TT zz)
		{
			x = xx;
			y = yy;
			z = zz;
		}
		
		template<typename T2>
		inline void set(const T2 *p)
		{
			x = TT(p[0]);
			y = TT(p[1]);
			z = TT(p[2]);
		}

		inline TT dot(const Vector3T &v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		inline friend TT dot(const Vector3T &v1, const Vector3T &v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		inline Vector3T cross(const Vector3T &v) const
		{
			return Vector3T(y * v.z - z * v.y,
							z * v.x - x * v.z,
							x * v.y - y * v.x);
		}

		inline friend Vector3T cross(const Vector3T &v1, const Vector3T &v2)
		{
			return Vector3T(v1.y * v2.z - v1.z * v2.y,
							v1.z * v2.x - v1.x * v2.z,
							v1.x * v2.y - v1.y * v2.x);
		}

		inline friend Vector3T operator*(const Vector3T &v, const TT &val)
		{
			return Vector3T(v.x*val, v.y*val, v.z*val);
		}

		inline friend Vector3T operator*(const TT &val, const Vector3T &v)
		{
			return Vector3T(val*v.x, val*v.y, val*v.z);
		}

		inline friend Vector3T operator*(const Vector3T &v1, const Vector3T &v2)
		{
			return Vector3T(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
		}

		inline friend Vector3T operator+(const Vector3T &v, const TT &val)
		{
			return Vector3T(v.x + val, v.y + val, v.z + val);
		}

		inline friend Vector3T operator+(const TT &val, const Vector3T &v)
		{
			return Vector3T(val + v.x, val + v.y, val + v.z);
		}

		inline friend Vector3T operator+(const Vector3T &v1, const Vector3T &v2)
		{
			return Vector3T(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		}

		inline friend Vector3T operator-(const Vector3T &v, const TT &val)
		{
			return Vector3T(v.x - val, v.y - val, v.z - val);
		}

		inline friend Vector3T operator-(const TT &val, const Vector3T &v)
		{
			return Vector3T(val - v.x, val - v.y, val - v.z);
		}

		inline friend Vector3T operator-(const Vector3T &v1, const Vector3T &v2)
		{
			return Vector3T(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		}

		inline friend Vector3T operator/(const Vector3T &v, const TT &val)
		{
			return Vector3T(v.x / val, v.y / val, v.z / val);
		}

		inline friend Vector3T operator/(const TT &val, const Vector3T &v)
		{
			return Vector3T(val / v.x, val / v.y, val / v.z);
		}

		inline friend Vector3T operator/(const Vector3T &v1, const Vector3T &v2)
		{
			return Vector3T(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
		}

		inline Vector3T &operator=(TT c)
		{
			x = c;
			y = c;
			z = c;
			return *this;
		}

		inline Vector3T &operator,(TT c)
		{
			y = z;
			z = c;
			return *this;
		}

		inline bool operator==(const Vector3T &v)
		{
			return (x == v.x) && (y == v.y) && (z = v.z);
		}

		inline bool operator<(const Vector3T &v)
		{
			return x < v.x;
		}

		inline Vector3T minimum(const Vector3T &v) const
		{
			return Vector3T((x<v.x ? x : v.x), (y<v.y ? y : v.y), (z<v.z ? z : v.z));
		}

		friend inline Vector3T minimum(const Vector3T &v1, const Vector3T &v2)
		{
			return v1.minimum(v2);
		}

		inline Vector3T maximum(const Vector3T &v) const
		{
			return Vector3T((x>v.x ? x : v.x), (y>v.y ? y : v.y), (z>v.z ? z : v.z));
		}

		friend inline Vector3T maximum(const Vector3T &v1, const Vector3T &v2)
		{
			return v1.maximum(v2);
		}

		inline TT dist(const Vector3T &v) const
		{
			return (v - *this).length();
		}

		friend inline TT dist(const Vector3T &v1, const Vector3T &v2)
		{
			return (v1 - v2).length();
		}

		inline Vector3T pow(const TT &e) const
		{
			return Vector3T(std::pow(x, e), std::pow(y, e), std::pow(z, e));
		}

		friend inline Vector3T pow(const Vector3T &v, const TT &e)
		{
			return v.pow(e);
		}

		inline Vector3T log() const
		{
			return Vector3T(std::log(x), std::log(y), std::log(z));
		}

		friend inline Vector3T log(const Vector3T &v)
		{
			return v.log();
		}

		inline Vector3T exp(const Vector3T &v) const
		{
			return Vector3T(std::exp(x), std::exp(y), std::exp(z));
		}

		friend inline Vector3T exp(const Vector3T &v)
		{
			return v.exp();
		}

		inline Vector3T abs() const
		{
			return Vector3T(std::fabs(x), std::fabs(y), std::fabs(z));
		}

		friend inline Vector3T abs(const Vector3T &v)
		{
			return v.abs();
		}

		inline Vector3T sign() const
		{
			return Vector3T(x>0 ? (TT)1.0 : (x<0 ? (TT) -1.0 : (TT)0.0), y>0 ? (TT)1.0 : (y<0 ? (TT) -1.0 : (TT)0.0), z>0 ? (TT)1.0 : (z<0 ? (TT) -1.0 : (TT)0.0));
		}

		friend inline Vector3T sign(const Vector3T &v)
		{
			return v.sign();
		}

		inline void toSRGB()
		{
			if (r <= (TT)0.0031308)
				r = r * (TT)12.92;
			else
				r = (TT)(1.055 * ::pow(r, 1.0 / 2.4) - 0.055);
			if (g <= (TT)0.0031308)
				g = g * (TT)12.92;
			else
				g = (TT)(1.055 * ::pow(g, 1.0 / 2.4) - 0.055);
			if (b <= (TT)0.0031308)
				b = b * (TT)12.92;
			else
				b = (TT)(1.055 * ::pow(b, 1.0 / 2.4) - 0.055);
		}

		inline void toLinear()
		{
			if (r <= (TT)0.04045)
				r = r / (TT)12.92;
			else
				r = (TT)::pow((r + 0.055) / 1.055, 2.4);
			if (g <= (TT)0.04045)
				g = g / (TT)12.92;
			else
				g = (TT)::pow((g + 0.055) / 1.055, 2.4);
			if (b <= (TT)0.04045)
				b = b / (TT)12.92;
			else
				b = (TT)::pow((b + 0.055) / 1.055, 2.4);
		}







		#define KF_SWIZZLE3D(a,b,c) inline Vector3T a##b##c() { return Vector3T(a, b, c); }
		KF_SWIZZLE3D(x, x, x) KF_SWIZZLE3D(x, x, y) KF_SWIZZLE3D(x, x, z) KF_SWIZZLE3D(x, y, x) KF_SWIZZLE3D(x, y, y) KF_SWIZZLE3D(x, y, z) KF_SWIZZLE3D(x, z, x) KF_SWIZZLE3D(x, z, y) KF_SWIZZLE3D(x, z, z)
		KF_SWIZZLE3D(y, x, x) KF_SWIZZLE3D(y, x, y) KF_SWIZZLE3D(y, x, z) KF_SWIZZLE3D(y, y, x) KF_SWIZZLE3D(y, y, y) KF_SWIZZLE3D(y, y, z) KF_SWIZZLE3D(y, z, x) KF_SWIZZLE3D(y, z, y) KF_SWIZZLE3D(y, z, z)
		KF_SWIZZLE3D(z, x, x) KF_SWIZZLE3D(z, x, y) KF_SWIZZLE3D(z, x, z) KF_SWIZZLE3D(z, y, x) KF_SWIZZLE3D(z, y, y) KF_SWIZZLE3D(z, y, z) KF_SWIZZLE3D(z, z, x) KF_SWIZZLE3D(z, z, y) KF_SWIZZLE3D(z, z, z)
		KF_SWIZZLE3D(r, r, r) KF_SWIZZLE3D(r, r, g) KF_SWIZZLE3D(r, r, b) KF_SWIZZLE3D(r, g, r) KF_SWIZZLE3D(r, g, g) KF_SWIZZLE3D(r, g, b) KF_SWIZZLE3D(r, b, r) KF_SWIZZLE3D(r, b, g) KF_SWIZZLE3D(r, b, b)
		KF_SWIZZLE3D(g, r, r) KF_SWIZZLE3D(g, r, g) KF_SWIZZLE3D(g, r, b) KF_SWIZZLE3D(g, g, r) KF_SWIZZLE3D(g, g, g) KF_SWIZZLE3D(g, g, b) KF_SWIZZLE3D(g, b, r) KF_SWIZZLE3D(g, b, g) KF_SWIZZLE3D(g, b, b)
		KF_SWIZZLE3D(b, r, r) KF_SWIZZLE3D(b, r, g) KF_SWIZZLE3D(b, r, b) KF_SWIZZLE3D(b, g, r) KF_SWIZZLE3D(b, g, g) KF_SWIZZLE3D(b, g, b) KF_SWIZZLE3D(b, b, r) KF_SWIZZLE3D(b, b, g) KF_SWIZZLE3D(b, b, b)
		#undef KF_SWIZZLE3D

		#define KF_SWIZZLE2D(a,b) inline Vector2T<TT> a##b() { return Vector2T<TT>(a, b); }
		KF_SWIZZLE2D(x, x) KF_SWIZZLE2D(x, y) KF_SWIZZLE2D(y, x) KF_SWIZZLE2D(y, y)
		KF_SWIZZLE2D(r, r) KF_SWIZZLE2D(r, g) KF_SWIZZLE2D(g, r) KF_SWIZZLE2D(g, g)
		KF_SWIZZLE2D(u, u) KF_SWIZZLE2D(u, v) KF_SWIZZLE2D(v, u) KF_SWIZZLE2D(v, v)
		#undef KF_SWIZZLE2D

		inline static Vector3T ZERO()
		{
			return Vector3T(0, 0, 0);
		}
		
		inline static Vector3T ONE()
		{
			return Vector3T(1, 1, 1);
		}

		inline static Vector3T UNIT_X()
		{
			return Vector3T(1, 0, 0);
		}

		inline static Vector3T UNIT_Y()
		{
			return Vector3T(0, 1, 0);
		}

		inline static Vector3T UNIT_Z()
		{
			return Vector3T(0, 0, 1);
		}

		inline static Vector3T NEGATIVE_UNIT_X()
		{
			return Vector3T(-1, 0, 0);
		}

		inline static Vector3T NEGATIVE_UNIT_Y()
		{
			return Vector3T(0, -1, 0);
		}

		inline static Vector3T NEGATIVE_UNIT_Z()
		{
			return Vector3T(0, 0, -1);
		}
	};

	template <typename T1, typename T2>
	T1 convertVector3(const T2 &v)
	{
		T1 result;
		result.x = v.x;
		result.y = v.y;
		result.z = v.z;
		return result;
	}

	
	typedef Vector3T<float>  Vector3f;
	typedef Vector3T<double> Vector3d;
	typedef Vector3T<float>  Vector3;
	typedef Vector3T<float> ColourRGB;
	typedef Vector3T<double> ColourRGBD;
	typedef Vector3T<float> Colour;

}

#endif

