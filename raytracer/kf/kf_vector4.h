////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_VECTOR4_HEADER
#define KF_VECTOR4_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector2.h"
#include "kf/kf_vector3.h"

#pragma warning( disable : 4201)

namespace kf
{
	template<typename TT>
	class Vector4T
	{
	public:
		typedef TT type;
		enum
		{
			size = 4
		};
		enum Elements
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1,
			Z = 2, B = 2,
			W = 3, A = 3
		};
		union
		{
			TT e[4];
			union
			{
				struct
				{
					TT x;
					TT y;
					TT z;
					TT w;
				};
				struct
				{
					TT r;
					TT g;
					TT b;
					TT a;
				};
				struct
				{
					TT u;
					TT v;
				};
			};
		};

		inline Vector4T() : x(0), y(0), z(0), w(0)
		{
		}

		inline Vector4T(const Vector4T &c) : x(c.x), y(c.y), z(c.z), w(c.w)
		{
		}

		inline Vector4T(const Vector2T<TT> &c, TT f1 = 0, TT f2 = 0) : x(c.x), y(c.y), z(f1), w(f2)
		{
		}

		inline Vector4T(TT f1, const Vector2T<TT> &c, TT f2 = 0) : x(f1), y(c.x), z(c.y), w(f2)
		{
		}

		inline Vector4T(TT f1, TT f2, const Vector2T<TT> &c) : x(f1), y(f2), z(c.x), w(c.y)
		{
		}

		inline Vector4T(const Vector3T<TT> &c, TT f1 = 0) : x(c.x), y(c.y), z(c.z), w(f1)
		{
		}

		inline Vector4T(TT f1, const Vector3T<TT> &c) : x(f1), y(c.x), z(c.y), w(c.z)
		{
		}

		inline Vector4T(const Vector2T<TT> &c1, const Vector2T<TT> &c2) : x(c1.x), y(c1.y), z(c2.x), w(c2.y)
		{
		}

		explicit inline Vector4T(TT xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
		{
		}

		template<typename T2>
		explicit inline Vector4T(const T2 *p) : x(TT(p[0])), y(TT(p[1])), z(TT(p[2])), w(TT(p[3]))
		{
		}

		inline Vector4T(TT xx, TT yy, TT zz, TT ww) : x(xx), y(yy), z(zz), w(ww)
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

		inline Vector4T operator*=(const TT &c)
		{
			x *= c;
			y *= c;
			z *= c;
			w *= c;
			return *this;
		}
		inline Vector4T operator/=(const TT &c)
		{
			x /= c;
			y /= c;
			z /= c;
			w /= c;
			return *this;
		}
		inline Vector4T operator+=(const Vector4T &c)
		{
			x += c.x;
			y += c.y;
			z += c.z;
			w += c.w;
			return *this;
		}
		inline Vector4T operator-=(const Vector4T &c)
		{
			x -= c.x;
			y -= c.y;
			z -= c.z;
			w -= c.w;
			return *this;
		}
		inline Vector4T operator*=(const Vector4T &c)
		{
			x *= c.x;
			y *= c.y;
			z *= c.z;
			w *= c.w;
			return *this;
		}
		inline Vector4T operator/=(const Vector4T &c)
		{
			x /= c.x;
			y /= c.y;
			z /= c.z;
			w /= c.w;
			return *this;
		}
		inline Vector4T operator=(const TT *p)
		{
			x = p[0];
			y = p[1];
			z = p[2];
			w = p[3];
			return *this;
		}
		inline Vector4T operator=(const Vector4T &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}

		inline float normalise()
		{
			TT l;
			l = TT(sqrt(x*x + y*y + z*z + w*w));
			if (l != 0.0)
			{
				set(x / l, y / l, z / l, w / l);
			}
			else
			{
				set(0, 0, 0, 0);
			}
			return l;
		}

		friend inline Vector4T normalise(const Vector4T &v)
		{
			Vector4T temp(v);
			temp.normalise();
			return temp;
		}

		inline TT length() const
		{
			return sqrt(x*x + y*y + z*z + w*w);
		}

		friend inline TT length(const Vector4T &v)
		{
			return v.length();
		}

		inline TT lengthSquared() const
		{
			return x*x + y*y + z*z + w*w;
		}

		friend inline TT lengthSquared(const Vector4T &v)
		{
			return v.lengthSquared();
		}

		inline Vector4T clamp(float low, float high) const
		{
			Vector4T v(*this);
			if (v.x < low) v.x = low;
			if (v.x > high) v.x = high;
			if (v.y < low) v.y = low;
			if (v.y > high) v.y = high;
			if (v.z < low) v.z = low;
			if (v.z > high) v.z = high;
			if (v.w < low) v.w = low;
			if (v.w > high) v.w = high;
			return v;
		}

		friend inline TT clamp(const Vector4T &v, float low, float high)
		{
			return v.clamp(low, high);
		}

		inline Vector4T clamp(const Vector4T &low, const Vector4T &high) const
		{
			Vector4T v(*this);
			if (v.x < low.x) v.x = low.x;
			if (v.x > high.x) v.x = high.x;
			if (v.y < low.y) v.y = low.y;
			if (v.y > high.y) v.y = high.y;
			if (v.z < low.z) v.z = low.z;
			if (v.z > high.z) v.z = high.z;
			if (v.w < low.w) v.w = low.w;
			if (v.w > high.w) v.w = high.w;
			return v;
		}

		friend inline TT clamp(const Vector4T &v, const Vector4T &low, const Vector4T &high)
		{
			return v.clamp(low, high);
		}

		inline Vector4T saturate() const
		{
			return clamp((TT) 0, (TT) 1);
		}

		inline Vector4T up() const
		{
			if (x != 0 || z != 0)
			{
				Vector4T v;
				v = (*this).cross(UNIT_Y()).cross(*this);
				v.normalise();
				return v;
			}
			return Vector4T::UNIT_Z();
		}

		friend inline Vector4T up(const Vector4T &v)
		{
			return v.up();
		}

		inline Vector4T right() const
		{
			if (x != 0 || z != 0)
			{
				Vector4T v;
				v = (*this).cross(UNIT_Y());
				v.normalise();
				return v;
			}
			return Vector4T::UNIT_Z();
		}

		friend inline Vector4T right(const Vector4T &v)
		{
			return v.right();
		}

		inline Vector4T reflect(const Vector4T &n) const
		{
			return (TT)2.0 * n * dot(n) - *this;
		}

		friend inline Vector4T reflect(const Vector4T &v, const Vector4T &n)
		{
			return v.reflect(n);
		}

		inline Vector4T dominantAxis() const
		{
			Vector4T v = abs();
			int j = 0;
			TT value = e[j];
			for (int i = 1; i<4; ++i)
			{
				if (e[i] > e[j])
				{
					j = i;
					value = e[i];
				}
			}
			switch (j)
			{
			case 0:
				return x >= 0 ? UNIT_X() : NEGATIVE_UNIT_X();
				break;
			case 1:
				return y >= 0 ? UNIT_Y() : NEGATIVE_UNIT_Y();
				break;
			case 2:
				return z >= 0 ? UNIT_Z() : NEGATIVE_UNIT_Z();
				break;
			case 3:
				return w >= 0 ? UNIT_W() : NEGATIVE_UNIT_W();
				break;
			}
		}

		friend inline Vector4T dominantAxis(const Vector4T &v)
		{
			return v.dominantAxis();
		}

		inline Vector4T swiz(Elements comp1, Elements comp2, Elements comp3, Elements comp4) const
		{
			return Vector4T(e[comp1], e[comp2], e[comp3], e[comp4]);
		}

		friend inline Vector4T swiz(const Vector4T &v, Elements comp1, Elements comp2, Elements comp3, Elements comp4)
		{
			return v.swiz(comp1, comp2, comp3, comp4);
		}

		inline void set(const Vector4T &value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
			w = value.w;
		}

		inline void set(TT xyzw)
		{
			x = y = z = w = xyzw;
		}

		inline void set(TT xx, TT yy, TT zz, TT ww)
		{
			x = xx;
			y = yy;
			z = zz;
			w = ww;
		}

		template<typename T2>
		inline void set(const T2 *p)
		{
			x = TT(p[0]);
			y = TT(p[1]);
			z = TT(p[2]);
			w = TT(p[3]);
		}

		inline TT dot(const Vector4T &v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		inline friend TT dot(const Vector4T &v1, const Vector4T &v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
		}

		inline Vector4T cross(const Vector4T &v) const
		{
			return Vector4T(y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x, 0);
		}

		inline friend Vector4T cross(const Vector4T &v1, const Vector4T &v2)
		{
			return Vector4T(v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x, 0);
		}

		inline friend Vector4T operator*(const Vector4T &v, const TT &val)
		{
			return Vector4T(v.x*val, v.y*val, v.z*val, v.w*val);
		}

		inline friend Vector4T operator*(const TT &val, const Vector4T &v)
		{
			return Vector4T(val*v.x, val*v.y, val*v.z, val*v.w);
		}

		inline friend Vector4T operator*(const Vector4T &v1, const Vector4T &v2)
		{
			return Vector4T(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z, v1.w*v2.w);
		}

		inline friend Vector4T operator+(const Vector4T &v, const TT &val)
		{
			return Vector4T(v.x + val, v.y + val, v.z + val, v.w + val);
		}

		inline friend Vector4T operator+(const TT &val, const Vector4T &v)
		{
			return Vector4T(val + v.x, val + v.y, val + v.z, val + v.w);
		}

		inline friend Vector4T operator+(const Vector4T &v1, const Vector4T &v2)
		{
			return Vector4T(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
		}

		inline friend Vector4T operator-(const Vector4T &v, const TT &val)
		{
			return Vector4T(v.x - val, v.y - val, v.z - val, v.w - val);
		}

		inline friend Vector4T operator-(const TT &val, const Vector4T &v)
		{
			return Vector4T(val - v.x, val - v.y, val - v.z, val - v.w);
		}

		inline friend Vector4T operator-(const Vector4T &v1, const Vector4T &v2)
		{
			return Vector4T(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
		}

		inline friend Vector4T operator/(const Vector4T &v, const TT &val)
		{
			return Vector4T(v.x / val, v.y / val, v.z / val, v.w / val);
		}

		inline friend Vector4T operator/(const TT &val, const Vector4T &v)
		{
			return Vector4T(val / v.x, val / v.y, val / v.z, val / v.w);
		}

		inline friend Vector4T operator/(const Vector4T &v1, const Vector4T &v2)
		{
			return Vector4T(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
		}

		inline Vector4T &operator=(TT c)
		{
			x = c;
			y = c;
			z = c;
			w = c;
			return *this;
		}

		inline Vector4T &operator,(TT c)
		{
			y = z;
			z = w;
			w = c;
			return *this;
		}

		inline bool operator==(const Vector4T &v)
		{
			return (x == v.x) && (y == v.y) && (z = v.z) && (w = v.w);
		}

		inline bool operator<(const Vector4T &v)
		{
			return x < v.x;
		}

		inline Vector4T minimum(const Vector4T &v) const
		{
			return Vector4T((x<v.x ? x : v.x), (y<v.y ? y : v.y), (z<v.z ? z : v.z), (w<v.w ? w : v.w));
		}

		friend inline Vector4T minimum(const Vector4T &v1, const Vector4T &v2)
		{
			return v1.minimum(v2);
		}

		inline Vector4T maximum(const Vector4T &v) const
		{
			return Vector4T((x>v.x ? x : v.x), (y>v.y ? y : v.y), (z>v.z ? z : v.z), (w>v.w ? z : v.w));
		}

		friend inline Vector4T maximum(const Vector4T &v1, const Vector4T &v2)
		{
			return v1.maximum(v2);
		}

		inline TT dist(const Vector4T &v) const
		{
			return (v - *this).length();
		}

		friend inline TT dist(const Vector4T &v1, const Vector4T &v2)
		{
			return (v1 - v2).length();
		}

		inline Vector4T pow(const TT &e) const
		{
			return Vector4T(std::pow(x, e), std::pow(y, e), std::pow(z, e), std::pow(w, e));
		}

		friend inline Vector4T pow(const Vector4T &v, const TT &e)
		{
			return v.pow(e);
		}

		inline Vector4T log() const
		{
			return Vector4T(std::log(x), std::log(y), std::log(z), , std::log(w));
		}

		friend inline Vector4T log(const Vector4T &v)
		{
			return v.log();
		}

		inline Vector4T exp(const Vector4T &v) const
		{
			return Vector4T(std::exp(x), std::exp(y), std::exp(z), std::exp(w));
		}

		friend inline Vector4T exp(const Vector4T &v)
		{
			return v.exp();
		}

		inline Vector4T abs() const
		{
			return Vector4T(std::fabs(x), std::fabs(y), std::fabs(z), std::fabs(w));
		}

		friend inline Vector4T abs(const Vector4T &v)
		{
			return v.abs();
		}

		inline Vector4T sign() const
		{
			return Vector4T(x>0 ? (TT)1.0 : (x<0 ? (TT) -1.0 : (TT)0.0), y>0 ? (TT)1.0 : (y<0 ? (TT) -1.0 : (TT)0.0), z>0 ? (TT)1.0 : (z<0 ? (TT) -1.0 : (TT)0.0), w>0 ? (TT)1.0 : (w<0 ? (TT) -1.0 : (TT)0.0));
		}

		friend inline Vector4T sign(const Vector4T &v)
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

#define KF_SWIZZLE4D(a,b,c,d) inline Vector4T a##b##c##d() { return Vector4T(a, b, c, d); }
		KF_SWIZZLE4D(x, x, x, x) KF_SWIZZLE4D(x, x, x, y) KF_SWIZZLE4D(x, x, x, z) KF_SWIZZLE4D(x, x, x, w) KF_SWIZZLE4D(x, x, y, x) KF_SWIZZLE4D(x, x, y, y) KF_SWIZZLE4D(x, x, y, z) KF_SWIZZLE4D(x, x, y, w) KF_SWIZZLE4D(x, x, z, x) KF_SWIZZLE4D(x, x, z, y) KF_SWIZZLE4D(x, x, z, z) KF_SWIZZLE4D(x, x, z, w) KF_SWIZZLE4D(x, x, w, x) KF_SWIZZLE4D(x, x, w, y) KF_SWIZZLE4D(x, x, w, z) KF_SWIZZLE4D(x, x, w, w) KF_SWIZZLE4D(x, y, x, x) KF_SWIZZLE4D(x, y, x, y) KF_SWIZZLE4D(x, y, x, z) KF_SWIZZLE4D(x, y, x, w) KF_SWIZZLE4D(x, y, y, x) KF_SWIZZLE4D(x, y, y, y) KF_SWIZZLE4D(x, y, y, z) KF_SWIZZLE4D(x, y, y, w) KF_SWIZZLE4D(x, y, z, x) KF_SWIZZLE4D(x, y, z, y) KF_SWIZZLE4D(x, y, z, z) KF_SWIZZLE4D(x, y, z, w) KF_SWIZZLE4D(x, y, w, x) KF_SWIZZLE4D(x, y, w, y) KF_SWIZZLE4D(x, y, w, z) KF_SWIZZLE4D(x, y, w, w) KF_SWIZZLE4D(x, z, x, x) KF_SWIZZLE4D(x, z, x, y) KF_SWIZZLE4D(x, z, x, z) KF_SWIZZLE4D(x, z, x, w) KF_SWIZZLE4D(x, z, y, x) KF_SWIZZLE4D(x, z, y, y) KF_SWIZZLE4D(x, z, y, z) KF_SWIZZLE4D(x, z, y, w) KF_SWIZZLE4D(x, z, z, x) KF_SWIZZLE4D(x, z, z, y) KF_SWIZZLE4D(x, z, z, z) KF_SWIZZLE4D(x, z, z, w) KF_SWIZZLE4D(x, z, w, x) KF_SWIZZLE4D(x, z, w, y) KF_SWIZZLE4D(x, z, w, z) KF_SWIZZLE4D(x, z, w, w) KF_SWIZZLE4D(x, w, x, x) KF_SWIZZLE4D(x, w, x, y) KF_SWIZZLE4D(x, w, x, z) KF_SWIZZLE4D(x, w, x, w) KF_SWIZZLE4D(x, w, y, x) KF_SWIZZLE4D(x, w, y, y) KF_SWIZZLE4D(x, w, y, z) KF_SWIZZLE4D(x, w, y, w) KF_SWIZZLE4D(x, w, z, x) KF_SWIZZLE4D(x, w, z, y) KF_SWIZZLE4D(x, w, z, z) KF_SWIZZLE4D(x, w, z, w) KF_SWIZZLE4D(x, w, w, x) KF_SWIZZLE4D(x, w, w, y) KF_SWIZZLE4D(x, w, w, z) KF_SWIZZLE4D(x, w, w, w)
		KF_SWIZZLE4D(y, x, x, x) KF_SWIZZLE4D(y, x, x, y) KF_SWIZZLE4D(y, x, x, z) KF_SWIZZLE4D(y, x, x, w) KF_SWIZZLE4D(y, x, y, x) KF_SWIZZLE4D(y, x, y, y) KF_SWIZZLE4D(y, x, y, z) KF_SWIZZLE4D(y, x, y, w) KF_SWIZZLE4D(y, x, z, x) KF_SWIZZLE4D(y, x, z, y) KF_SWIZZLE4D(y, x, z, z) KF_SWIZZLE4D(y, x, z, w) KF_SWIZZLE4D(y, x, w, x) KF_SWIZZLE4D(y, x, w, y) KF_SWIZZLE4D(y, x, w, z) KF_SWIZZLE4D(y, x, w, w) KF_SWIZZLE4D(y, y, x, x) KF_SWIZZLE4D(y, y, x, y) KF_SWIZZLE4D(y, y, x, z) KF_SWIZZLE4D(y, y, x, w) KF_SWIZZLE4D(y, y, y, x) KF_SWIZZLE4D(y, y, y, y) KF_SWIZZLE4D(y, y, y, z) KF_SWIZZLE4D(y, y, y, w) KF_SWIZZLE4D(y, y, z, x) KF_SWIZZLE4D(y, y, z, y) KF_SWIZZLE4D(y, y, z, z) KF_SWIZZLE4D(y, y, z, w) KF_SWIZZLE4D(y, y, w, x) KF_SWIZZLE4D(y, y, w, y) KF_SWIZZLE4D(y, y, w, z) KF_SWIZZLE4D(y, y, w, w) KF_SWIZZLE4D(y, z, x, x) KF_SWIZZLE4D(y, z, x, y) KF_SWIZZLE4D(y, z, x, z) KF_SWIZZLE4D(y, z, x, w) KF_SWIZZLE4D(y, z, y, x) KF_SWIZZLE4D(y, z, y, y) KF_SWIZZLE4D(y, z, y, z) KF_SWIZZLE4D(y, z, y, w) KF_SWIZZLE4D(y, z, z, x) KF_SWIZZLE4D(y, z, z, y) KF_SWIZZLE4D(y, z, z, z) KF_SWIZZLE4D(y, z, z, w) KF_SWIZZLE4D(y, z, w, x) KF_SWIZZLE4D(y, z, w, y) KF_SWIZZLE4D(y, z, w, z) KF_SWIZZLE4D(y, z, w, w) KF_SWIZZLE4D(y, w, x, x) KF_SWIZZLE4D(y, w, x, y) KF_SWIZZLE4D(y, w, x, z) KF_SWIZZLE4D(y, w, x, w) KF_SWIZZLE4D(y, w, y, x) KF_SWIZZLE4D(y, w, y, y) KF_SWIZZLE4D(y, w, y, z) KF_SWIZZLE4D(y, w, y, w) KF_SWIZZLE4D(y, w, z, x) KF_SWIZZLE4D(y, w, z, y) KF_SWIZZLE4D(y, w, z, z) KF_SWIZZLE4D(y, w, z, w) KF_SWIZZLE4D(y, w, w, x) KF_SWIZZLE4D(y, w, w, y) KF_SWIZZLE4D(y, w, w, z) KF_SWIZZLE4D(y, w, w, w)
		KF_SWIZZLE4D(z, x, x, x) KF_SWIZZLE4D(z, x, x, y) KF_SWIZZLE4D(z, x, x, z) KF_SWIZZLE4D(z, x, x, w) KF_SWIZZLE4D(z, x, y, x) KF_SWIZZLE4D(z, x, y, y) KF_SWIZZLE4D(z, x, y, z) KF_SWIZZLE4D(z, x, y, w) KF_SWIZZLE4D(z, x, z, x) KF_SWIZZLE4D(z, x, z, y) KF_SWIZZLE4D(z, x, z, z) KF_SWIZZLE4D(z, x, z, w) KF_SWIZZLE4D(z, x, w, x) KF_SWIZZLE4D(z, x, w, y) KF_SWIZZLE4D(z, x, w, z) KF_SWIZZLE4D(z, x, w, w) KF_SWIZZLE4D(z, y, x, x) KF_SWIZZLE4D(z, y, x, y) KF_SWIZZLE4D(z, y, x, z) KF_SWIZZLE4D(z, y, x, w) KF_SWIZZLE4D(z, y, y, x) KF_SWIZZLE4D(z, y, y, y) KF_SWIZZLE4D(z, y, y, z) KF_SWIZZLE4D(z, y, y, w) KF_SWIZZLE4D(z, y, z, x) KF_SWIZZLE4D(z, y, z, y) KF_SWIZZLE4D(z, y, z, z) KF_SWIZZLE4D(z, y, z, w) KF_SWIZZLE4D(z, y, w, x) KF_SWIZZLE4D(z, y, w, y) KF_SWIZZLE4D(z, y, w, z) KF_SWIZZLE4D(z, y, w, w) KF_SWIZZLE4D(z, z, x, x) KF_SWIZZLE4D(z, z, x, y) KF_SWIZZLE4D(z, z, x, z) KF_SWIZZLE4D(z, z, x, w) KF_SWIZZLE4D(z, z, y, x) KF_SWIZZLE4D(z, z, y, y) KF_SWIZZLE4D(z, z, y, z) KF_SWIZZLE4D(z, z, y, w) KF_SWIZZLE4D(z, z, z, x) KF_SWIZZLE4D(z, z, z, y) KF_SWIZZLE4D(z, z, z, z) KF_SWIZZLE4D(z, z, z, w) KF_SWIZZLE4D(z, z, w, x) KF_SWIZZLE4D(z, z, w, y) KF_SWIZZLE4D(z, z, w, z) KF_SWIZZLE4D(z, z, w, w) KF_SWIZZLE4D(z, w, x, x) KF_SWIZZLE4D(z, w, x, y) KF_SWIZZLE4D(z, w, x, z) KF_SWIZZLE4D(z, w, x, w) KF_SWIZZLE4D(z, w, y, x) KF_SWIZZLE4D(z, w, y, y) KF_SWIZZLE4D(z, w, y, z) KF_SWIZZLE4D(z, w, y, w) KF_SWIZZLE4D(z, w, z, x) KF_SWIZZLE4D(z, w, z, y) KF_SWIZZLE4D(z, w, z, z) KF_SWIZZLE4D(z, w, z, w) KF_SWIZZLE4D(z, w, w, x) KF_SWIZZLE4D(z, w, w, y) KF_SWIZZLE4D(z, w, w, z) KF_SWIZZLE4D(z, w, w, w)
		KF_SWIZZLE4D(w, x, x, x) KF_SWIZZLE4D(w, x, x, y) KF_SWIZZLE4D(w, x, x, z) KF_SWIZZLE4D(w, x, x, w) KF_SWIZZLE4D(w, x, y, x) KF_SWIZZLE4D(w, x, y, y) KF_SWIZZLE4D(w, x, y, z) KF_SWIZZLE4D(w, x, y, w) KF_SWIZZLE4D(w, x, z, x) KF_SWIZZLE4D(w, x, z, y) KF_SWIZZLE4D(w, x, z, z) KF_SWIZZLE4D(w, x, z, w) KF_SWIZZLE4D(w, x, w, x) KF_SWIZZLE4D(w, x, w, y) KF_SWIZZLE4D(w, x, w, z) KF_SWIZZLE4D(w, x, w, w) KF_SWIZZLE4D(w, y, x, x) KF_SWIZZLE4D(w, y, x, y) KF_SWIZZLE4D(w, y, x, z) KF_SWIZZLE4D(w, y, x, w) KF_SWIZZLE4D(w, y, y, x) KF_SWIZZLE4D(w, y, y, y) KF_SWIZZLE4D(w, y, y, z) KF_SWIZZLE4D(w, y, y, w) KF_SWIZZLE4D(w, y, z, x) KF_SWIZZLE4D(w, y, z, y) KF_SWIZZLE4D(w, y, z, z) KF_SWIZZLE4D(w, y, z, w) KF_SWIZZLE4D(w, y, w, x) KF_SWIZZLE4D(w, y, w, y) KF_SWIZZLE4D(w, y, w, z) KF_SWIZZLE4D(w, y, w, w) KF_SWIZZLE4D(w, z, x, x) KF_SWIZZLE4D(w, z, x, y) KF_SWIZZLE4D(w, z, x, z) KF_SWIZZLE4D(w, z, x, w) KF_SWIZZLE4D(w, z, y, x) KF_SWIZZLE4D(w, z, y, y) KF_SWIZZLE4D(w, z, y, z) KF_SWIZZLE4D(w, z, y, w) KF_SWIZZLE4D(w, z, z, x) KF_SWIZZLE4D(w, z, z, y) KF_SWIZZLE4D(w, z, z, z) KF_SWIZZLE4D(w, z, z, w) KF_SWIZZLE4D(w, z, w, x) KF_SWIZZLE4D(w, z, w, y) KF_SWIZZLE4D(w, z, w, z) KF_SWIZZLE4D(w, z, w, w) KF_SWIZZLE4D(w, w, x, x) KF_SWIZZLE4D(w, w, x, y) KF_SWIZZLE4D(w, w, x, z) KF_SWIZZLE4D(w, w, x, w) KF_SWIZZLE4D(w, w, y, x) KF_SWIZZLE4D(w, w, y, y) KF_SWIZZLE4D(w, w, y, z) KF_SWIZZLE4D(w, w, y, w) KF_SWIZZLE4D(w, w, z, x) KF_SWIZZLE4D(w, w, z, y) KF_SWIZZLE4D(w, w, z, z) KF_SWIZZLE4D(w, w, z, w) KF_SWIZZLE4D(w, w, w, x) KF_SWIZZLE4D(w, w, w, y) KF_SWIZZLE4D(w, w, w, z) KF_SWIZZLE4D(w, w, w, w)
		KF_SWIZZLE4D(r, r, r, r) KF_SWIZZLE4D(r, r, r, g) KF_SWIZZLE4D(r, r, r, b) KF_SWIZZLE4D(r, r, r, a) KF_SWIZZLE4D(r, r, g, r) KF_SWIZZLE4D(r, r, g, g) KF_SWIZZLE4D(r, r, g, b) KF_SWIZZLE4D(r, r, g, a) KF_SWIZZLE4D(r, r, b, r) KF_SWIZZLE4D(r, r, b, g) KF_SWIZZLE4D(r, r, b, b) KF_SWIZZLE4D(r, r, b, a) KF_SWIZZLE4D(r, r, a, r) KF_SWIZZLE4D(r, r, a, g) KF_SWIZZLE4D(r, r, a, b) KF_SWIZZLE4D(r, r, a, a) KF_SWIZZLE4D(r, g, r, r) KF_SWIZZLE4D(r, g, r, g) KF_SWIZZLE4D(r, g, r, b) KF_SWIZZLE4D(r, g, r, a) KF_SWIZZLE4D(r, g, g, r) KF_SWIZZLE4D(r, g, g, g) KF_SWIZZLE4D(r, g, g, b) KF_SWIZZLE4D(r, g, g, a) KF_SWIZZLE4D(r, g, b, r) KF_SWIZZLE4D(r, g, b, g) KF_SWIZZLE4D(r, g, b, b) KF_SWIZZLE4D(r, g, b, a) KF_SWIZZLE4D(r, g, a, r) KF_SWIZZLE4D(r, g, a, g) KF_SWIZZLE4D(r, g, a, b) KF_SWIZZLE4D(r, g, a, a) KF_SWIZZLE4D(r, b, r, r) KF_SWIZZLE4D(r, b, r, g) KF_SWIZZLE4D(r, b, r, b) KF_SWIZZLE4D(r, b, r, a) KF_SWIZZLE4D(r, b, g, r) KF_SWIZZLE4D(r, b, g, g) KF_SWIZZLE4D(r, b, g, b) KF_SWIZZLE4D(r, b, g, a) KF_SWIZZLE4D(r, b, b, r) KF_SWIZZLE4D(r, b, b, g) KF_SWIZZLE4D(r, b, b, b) KF_SWIZZLE4D(r, b, b, a) KF_SWIZZLE4D(r, b, a, r) KF_SWIZZLE4D(r, b, a, g) KF_SWIZZLE4D(r, b, a, b) KF_SWIZZLE4D(r, b, a, a) KF_SWIZZLE4D(r, a, r, r) KF_SWIZZLE4D(r, a, r, g) KF_SWIZZLE4D(r, a, r, b) KF_SWIZZLE4D(r, a, r, a) KF_SWIZZLE4D(r, a, g, r) KF_SWIZZLE4D(r, a, g, g) KF_SWIZZLE4D(r, a, g, b) KF_SWIZZLE4D(r, a, g, a) KF_SWIZZLE4D(r, a, b, r) KF_SWIZZLE4D(r, a, b, g) KF_SWIZZLE4D(r, a, b, b) KF_SWIZZLE4D(r, a, b, a) KF_SWIZZLE4D(r, a, a, r) KF_SWIZZLE4D(r, a, a, g) KF_SWIZZLE4D(r, a, a, b) KF_SWIZZLE4D(r, a, a, a)
		KF_SWIZZLE4D(g, r, r, r) KF_SWIZZLE4D(g, r, r, g) KF_SWIZZLE4D(g, r, r, b) KF_SWIZZLE4D(g, r, r, a) KF_SWIZZLE4D(g, r, g, r) KF_SWIZZLE4D(g, r, g, g) KF_SWIZZLE4D(g, r, g, b) KF_SWIZZLE4D(g, r, g, a) KF_SWIZZLE4D(g, r, b, r) KF_SWIZZLE4D(g, r, b, g) KF_SWIZZLE4D(g, r, b, b) KF_SWIZZLE4D(g, r, b, a) KF_SWIZZLE4D(g, r, a, r) KF_SWIZZLE4D(g, r, a, g) KF_SWIZZLE4D(g, r, a, b) KF_SWIZZLE4D(g, r, a, a) KF_SWIZZLE4D(g, g, r, r) KF_SWIZZLE4D(g, g, r, g) KF_SWIZZLE4D(g, g, r, b) KF_SWIZZLE4D(g, g, r, a) KF_SWIZZLE4D(g, g, g, r) KF_SWIZZLE4D(g, g, g, g) KF_SWIZZLE4D(g, g, g, b) KF_SWIZZLE4D(g, g, g, a) KF_SWIZZLE4D(g, g, b, r) KF_SWIZZLE4D(g, g, b, g) KF_SWIZZLE4D(g, g, b, b) KF_SWIZZLE4D(g, g, b, a) KF_SWIZZLE4D(g, g, a, r) KF_SWIZZLE4D(g, g, a, g) KF_SWIZZLE4D(g, g, a, b) KF_SWIZZLE4D(g, g, a, a) KF_SWIZZLE4D(g, b, r, r) KF_SWIZZLE4D(g, b, r, g) KF_SWIZZLE4D(g, b, r, b) KF_SWIZZLE4D(g, b, r, a) KF_SWIZZLE4D(g, b, g, r) KF_SWIZZLE4D(g, b, g, g) KF_SWIZZLE4D(g, b, g, b) KF_SWIZZLE4D(g, b, g, a) KF_SWIZZLE4D(g, b, b, r) KF_SWIZZLE4D(g, b, b, g) KF_SWIZZLE4D(g, b, b, b) KF_SWIZZLE4D(g, b, b, a) KF_SWIZZLE4D(g, b, a, r) KF_SWIZZLE4D(g, b, a, g) KF_SWIZZLE4D(g, b, a, b) KF_SWIZZLE4D(g, b, a, a) KF_SWIZZLE4D(g, a, r, r) KF_SWIZZLE4D(g, a, r, g) KF_SWIZZLE4D(g, a, r, b) KF_SWIZZLE4D(g, a, r, a) KF_SWIZZLE4D(g, a, g, r) KF_SWIZZLE4D(g, a, g, g) KF_SWIZZLE4D(g, a, g, b) KF_SWIZZLE4D(g, a, g, a) KF_SWIZZLE4D(g, a, b, r) KF_SWIZZLE4D(g, a, b, g) KF_SWIZZLE4D(g, a, b, b) KF_SWIZZLE4D(g, a, b, a) KF_SWIZZLE4D(g, a, a, r) KF_SWIZZLE4D(g, a, a, g) KF_SWIZZLE4D(g, a, a, b) KF_SWIZZLE4D(g, a, a, a)
		KF_SWIZZLE4D(b, r, r, r) KF_SWIZZLE4D(b, r, r, g) KF_SWIZZLE4D(b, r, r, b) KF_SWIZZLE4D(b, r, r, a) KF_SWIZZLE4D(b, r, g, r) KF_SWIZZLE4D(b, r, g, g) KF_SWIZZLE4D(b, r, g, b) KF_SWIZZLE4D(b, r, g, a) KF_SWIZZLE4D(b, r, b, r) KF_SWIZZLE4D(b, r, b, g) KF_SWIZZLE4D(b, r, b, b) KF_SWIZZLE4D(b, r, b, a) KF_SWIZZLE4D(b, r, a, r) KF_SWIZZLE4D(b, r, a, g) KF_SWIZZLE4D(b, r, a, b) KF_SWIZZLE4D(b, r, a, a) KF_SWIZZLE4D(b, g, r, r) KF_SWIZZLE4D(b, g, r, g) KF_SWIZZLE4D(b, g, r, b) KF_SWIZZLE4D(b, g, r, a) KF_SWIZZLE4D(b, g, g, r) KF_SWIZZLE4D(b, g, g, g) KF_SWIZZLE4D(b, g, g, b) KF_SWIZZLE4D(b, g, g, a) KF_SWIZZLE4D(b, g, b, r) KF_SWIZZLE4D(b, g, b, g) KF_SWIZZLE4D(b, g, b, b) KF_SWIZZLE4D(b, g, b, a) KF_SWIZZLE4D(b, g, a, r) KF_SWIZZLE4D(b, g, a, g) KF_SWIZZLE4D(b, g, a, b) KF_SWIZZLE4D(b, g, a, a) KF_SWIZZLE4D(b, b, r, r) KF_SWIZZLE4D(b, b, r, g) KF_SWIZZLE4D(b, b, r, b) KF_SWIZZLE4D(b, b, r, a) KF_SWIZZLE4D(b, b, g, r) KF_SWIZZLE4D(b, b, g, g) KF_SWIZZLE4D(b, b, g, b) KF_SWIZZLE4D(b, b, g, a) KF_SWIZZLE4D(b, b, b, r) KF_SWIZZLE4D(b, b, b, g) KF_SWIZZLE4D(b, b, b, b) KF_SWIZZLE4D(b, b, b, a) KF_SWIZZLE4D(b, b, a, r) KF_SWIZZLE4D(b, b, a, g) KF_SWIZZLE4D(b, b, a, b) KF_SWIZZLE4D(b, b, a, a) KF_SWIZZLE4D(b, a, r, r) KF_SWIZZLE4D(b, a, r, g) KF_SWIZZLE4D(b, a, r, b) KF_SWIZZLE4D(b, a, r, a) KF_SWIZZLE4D(b, a, g, r) KF_SWIZZLE4D(b, a, g, g) KF_SWIZZLE4D(b, a, g, b) KF_SWIZZLE4D(b, a, g, a) KF_SWIZZLE4D(b, a, b, r) KF_SWIZZLE4D(b, a, b, g) KF_SWIZZLE4D(b, a, b, b) KF_SWIZZLE4D(b, a, b, a) KF_SWIZZLE4D(b, a, a, r) KF_SWIZZLE4D(b, a, a, g) KF_SWIZZLE4D(b, a, a, b) KF_SWIZZLE4D(b, a, a, a)
		KF_SWIZZLE4D(a, r, r, r) KF_SWIZZLE4D(a, r, r, g) KF_SWIZZLE4D(a, r, r, b) KF_SWIZZLE4D(a, r, r, a) KF_SWIZZLE4D(a, r, g, r) KF_SWIZZLE4D(a, r, g, g) KF_SWIZZLE4D(a, r, g, b) KF_SWIZZLE4D(a, r, g, a) KF_SWIZZLE4D(a, r, b, r) KF_SWIZZLE4D(a, r, b, g) KF_SWIZZLE4D(a, r, b, b) KF_SWIZZLE4D(a, r, b, a) KF_SWIZZLE4D(a, r, a, r) KF_SWIZZLE4D(a, r, a, g) KF_SWIZZLE4D(a, r, a, b) KF_SWIZZLE4D(a, r, a, a) KF_SWIZZLE4D(a, g, r, r) KF_SWIZZLE4D(a, g, r, g) KF_SWIZZLE4D(a, g, r, b) KF_SWIZZLE4D(a, g, r, a) KF_SWIZZLE4D(a, g, g, r) KF_SWIZZLE4D(a, g, g, g) KF_SWIZZLE4D(a, g, g, b) KF_SWIZZLE4D(a, g, g, a) KF_SWIZZLE4D(a, g, b, r) KF_SWIZZLE4D(a, g, b, g) KF_SWIZZLE4D(a, g, b, b) KF_SWIZZLE4D(a, g, b, a) KF_SWIZZLE4D(a, g, a, r) KF_SWIZZLE4D(a, g, a, g) KF_SWIZZLE4D(a, g, a, b) KF_SWIZZLE4D(a, g, a, a) KF_SWIZZLE4D(a, b, r, r) KF_SWIZZLE4D(a, b, r, g) KF_SWIZZLE4D(a, b, r, b) KF_SWIZZLE4D(a, b, r, a) KF_SWIZZLE4D(a, b, g, r) KF_SWIZZLE4D(a, b, g, g) KF_SWIZZLE4D(a, b, g, b) KF_SWIZZLE4D(a, b, g, a) KF_SWIZZLE4D(a, b, b, r) KF_SWIZZLE4D(a, b, b, g) KF_SWIZZLE4D(a, b, b, b) KF_SWIZZLE4D(a, b, b, a) KF_SWIZZLE4D(a, b, a, r) KF_SWIZZLE4D(a, b, a, g) KF_SWIZZLE4D(a, b, a, b) KF_SWIZZLE4D(a, b, a, a) KF_SWIZZLE4D(a, a, r, r) KF_SWIZZLE4D(a, a, r, g) KF_SWIZZLE4D(a, a, r, b) KF_SWIZZLE4D(a, a, r, a) KF_SWIZZLE4D(a, a, g, r) KF_SWIZZLE4D(a, a, g, g) KF_SWIZZLE4D(a, a, g, b) KF_SWIZZLE4D(a, a, g, a) KF_SWIZZLE4D(a, a, b, r) KF_SWIZZLE4D(a, a, b, g) KF_SWIZZLE4D(a, a, b, b) KF_SWIZZLE4D(a, a, b, a) KF_SWIZZLE4D(a, a, a, r) KF_SWIZZLE4D(a, a, a, g) KF_SWIZZLE4D(a, a, a, b) KF_SWIZZLE4D(a, a, a, a)
#undef KF_SWIZZLE4D

#define KF_SWIZZLE3D(a,b,c) inline Vector3T<TT> a##b##c() { return Vector3T<TT>(a, b, c); }
		KF_SWIZZLE3D(x, x, x) KF_SWIZZLE3D(x, x, y) KF_SWIZZLE3D(x, x, z) KF_SWIZZLE3D(x, x, w) KF_SWIZZLE3D(x, y, x) KF_SWIZZLE3D(x, y, y) KF_SWIZZLE3D(x, y, z) KF_SWIZZLE3D(x, y, w) KF_SWIZZLE3D(x, z, x) KF_SWIZZLE3D(x, z, y) KF_SWIZZLE3D(x, z, z) KF_SWIZZLE3D(x, z, w) KF_SWIZZLE3D(x, w, x) KF_SWIZZLE3D(x, w, y) KF_SWIZZLE3D(x, w, z) KF_SWIZZLE3D(x, w, w)
		KF_SWIZZLE3D(y, x, x) KF_SWIZZLE3D(y, x, y) KF_SWIZZLE3D(y, x, z) KF_SWIZZLE3D(y, x, w) KF_SWIZZLE3D(y, y, x) KF_SWIZZLE3D(y, y, y) KF_SWIZZLE3D(y, y, z) KF_SWIZZLE3D(y, y, w) KF_SWIZZLE3D(y, z, x) KF_SWIZZLE3D(y, z, y) KF_SWIZZLE3D(y, z, z) KF_SWIZZLE3D(y, z, w) KF_SWIZZLE3D(y, w, x) KF_SWIZZLE3D(y, w, y) KF_SWIZZLE3D(y, w, z) KF_SWIZZLE3D(y, w, w)
		KF_SWIZZLE3D(z, x, x) KF_SWIZZLE3D(z, x, y) KF_SWIZZLE3D(z, x, z) KF_SWIZZLE3D(z, x, w) KF_SWIZZLE3D(z, y, x) KF_SWIZZLE3D(z, y, y) KF_SWIZZLE3D(z, y, z) KF_SWIZZLE3D(z, y, w) KF_SWIZZLE3D(z, z, x) KF_SWIZZLE3D(z, z, y) KF_SWIZZLE3D(z, z, z) KF_SWIZZLE3D(z, z, w) KF_SWIZZLE3D(z, w, x) KF_SWIZZLE3D(z, w, y) KF_SWIZZLE3D(z, w, z) KF_SWIZZLE3D(z, w, w)
		KF_SWIZZLE3D(w, x, x) KF_SWIZZLE3D(w, x, y) KF_SWIZZLE3D(w, x, z) KF_SWIZZLE3D(w, x, w) KF_SWIZZLE3D(w, y, x) KF_SWIZZLE3D(w, y, y) KF_SWIZZLE3D(w, y, z) KF_SWIZZLE3D(w, y, w) KF_SWIZZLE3D(w, z, x) KF_SWIZZLE3D(w, z, y) KF_SWIZZLE3D(w, z, z) KF_SWIZZLE3D(w, z, w) KF_SWIZZLE3D(w, w, x) KF_SWIZZLE3D(w, w, y) KF_SWIZZLE3D(w, w, z) KF_SWIZZLE3D(w, w, w)
		KF_SWIZZLE3D(r, r, r) KF_SWIZZLE3D(r, r, g) KF_SWIZZLE3D(r, r, b) KF_SWIZZLE3D(r, r, a) KF_SWIZZLE3D(r, g, r) KF_SWIZZLE3D(r, g, g) KF_SWIZZLE3D(r, g, b) KF_SWIZZLE3D(r, g, a) KF_SWIZZLE3D(r, b, r) KF_SWIZZLE3D(r, b, g) KF_SWIZZLE3D(r, b, b) KF_SWIZZLE3D(r, b, a) KF_SWIZZLE3D(r, a, r) KF_SWIZZLE3D(r, a, g) KF_SWIZZLE3D(r, a, b) KF_SWIZZLE3D(r, a, a)
		KF_SWIZZLE3D(g, r, r) KF_SWIZZLE3D(g, r, g) KF_SWIZZLE3D(g, r, b) KF_SWIZZLE3D(g, r, a) KF_SWIZZLE3D(g, g, r) KF_SWIZZLE3D(g, g, g) KF_SWIZZLE3D(g, g, b) KF_SWIZZLE3D(g, g, a) KF_SWIZZLE3D(g, b, r) KF_SWIZZLE3D(g, b, g) KF_SWIZZLE3D(g, b, b) KF_SWIZZLE3D(g, b, a) KF_SWIZZLE3D(g, a, r) KF_SWIZZLE3D(g, a, g) KF_SWIZZLE3D(g, a, b) KF_SWIZZLE3D(g, a, a)
		KF_SWIZZLE3D(b, r, r) KF_SWIZZLE3D(b, r, g) KF_SWIZZLE3D(b, r, b) KF_SWIZZLE3D(b, r, a) KF_SWIZZLE3D(b, g, r) KF_SWIZZLE3D(b, g, g) KF_SWIZZLE3D(b, g, b) KF_SWIZZLE3D(b, g, a) KF_SWIZZLE3D(b, b, r) KF_SWIZZLE3D(b, b, g) KF_SWIZZLE3D(b, b, b) KF_SWIZZLE3D(b, b, a) KF_SWIZZLE3D(b, a, r) KF_SWIZZLE3D(b, a, g) KF_SWIZZLE3D(b, a, b) KF_SWIZZLE3D(b, a, a)
		KF_SWIZZLE3D(a, r, r) KF_SWIZZLE3D(a, r, g) KF_SWIZZLE3D(a, r, b) KF_SWIZZLE3D(a, r, a) KF_SWIZZLE3D(a, g, r) KF_SWIZZLE3D(a, g, g) KF_SWIZZLE3D(a, g, b) KF_SWIZZLE3D(a, g, a) KF_SWIZZLE3D(a, b, r) KF_SWIZZLE3D(a, b, g) KF_SWIZZLE3D(a, b, b) KF_SWIZZLE3D(a, b, a) KF_SWIZZLE3D(a, a, r) KF_SWIZZLE3D(a, a, g) KF_SWIZZLE3D(a, a, b) KF_SWIZZLE3D(a, a, a)
#undef KF_SWIZZLE3D

#define KF_SWIZZLE2D(a,b) inline Vector2T<TT> a##b() { return Vector2T<TT>(a, b); }
		KF_SWIZZLE2D(x, x) KF_SWIZZLE2D(x, y) KF_SWIZZLE2D(x, z) KF_SWIZZLE2D(x, w)
		KF_SWIZZLE2D(y, x) KF_SWIZZLE2D(y, y) KF_SWIZZLE2D(y, z) KF_SWIZZLE2D(y, w)
		KF_SWIZZLE2D(z, x) KF_SWIZZLE2D(z, y) KF_SWIZZLE2D(z, z) KF_SWIZZLE2D(z, w)
		KF_SWIZZLE2D(w, x) KF_SWIZZLE2D(w, y) KF_SWIZZLE2D(w, z) KF_SWIZZLE2D(w, w)
		KF_SWIZZLE2D(r, r) KF_SWIZZLE2D(r, g) KF_SWIZZLE2D(r, b) KF_SWIZZLE2D(r, a)
		KF_SWIZZLE2D(g, r) KF_SWIZZLE2D(g, g) KF_SWIZZLE2D(g, b) KF_SWIZZLE2D(g, a)
		KF_SWIZZLE2D(b, r) KF_SWIZZLE2D(b, g) KF_SWIZZLE2D(b, b) KF_SWIZZLE2D(b, a)
		KF_SWIZZLE2D(a, r) KF_SWIZZLE2D(a, g) KF_SWIZZLE2D(a, b) KF_SWIZZLE2D(a, a)
		KF_SWIZZLE2D(u, u) KF_SWIZZLE2D(u, v) KF_SWIZZLE2D(v, u) KF_SWIZZLE2D(v, v)
#undef KF_SWIZZLE2D

		inline static Vector4T ZERO()
		{
			return Vector4T(0, 0, 0, 0);
		}

		inline static Vector4T ONE()
		{
			return Vector4T(1, 1, 1, 1);
		}

		inline static Vector4T UNIT_X()
		{
			return Vector4T(1, 0, 0);
		}

		inline static Vector4T UNIT_Y()
		{
			return Vector4T(0, 1, 0);
		}

		inline static Vector4T UNIT_Z()
		{
			return Vector4T(0, 0, 1);
		}

		inline static Vector4T UNIT_W()
		{
			return Vector4T(0, 0, 0, 1);
		}

		inline static Vector4T NEGATIVE_UNIT_X()
		{
			return Vector4T(-1, 0, 0);
		}

		inline static Vector4T NEGATIVE_UNIT_Y()
		{
			return Vector4T(0, -1, 0);
		}

		inline static Vector4T NEGATIVE_UNIT_Z()
		{
			return Vector4T(0, 0, -1);
		}

		inline static Vector4T NEGATIVE_UNIT_W()
		{
			return Vector4T(0, 0, 0, -1);
		}
	};

	template <typename T1, typename T2>
	T1 convertVector4(const T2 &v)
	{
		T1 result;
		result.x = v.x;
		result.y = v.y;
		result.z = v.z;
		result.w = v.w;
		return result;
	}


	typedef Vector4T<float>  Vector4f;
	typedef Vector4T<double> Vector4d;
	typedef Vector4T<float>  Vector4;
	typedef Vector4T<float> ColourRGBA;
	typedef Vector4T<double> ColourRGBAD;

}

#endif

