////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_VECTOR2_HEADER
#define KF_VECTOR2_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"

#pragma warning( disable : 4201)

namespace kf
{
	template<typename TT>
	class Vector2T
	{
	public:
		typedef TT type;
		enum
		{
			size = 2
		};
		enum Elements
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1
		};
		union
		{
			TT e[2];
			union
			{
				struct
				{
					TT x;
					TT y;
				};
				struct
				{
					TT r;
					TT g;
				};
				struct
				{
					TT u;
					TT v;
				};
			};
		};

		inline Vector2T() : x(0), y(0)
		{
		}

		inline Vector2T(const Vector2T &c) : x(c.x), y(c.y)
		{
		}

		explicit inline Vector2T(TT xy) : x(xy), y(xy)
		{
		}

		template<typename T2>
		explicit inline Vector2T(const T2 *p) : x(TT(p[0])), y(TT(p[1]))
		{
		}

		inline Vector2T(TT xx, TT yy) : x(xx), y(yy)
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

		inline Vector2T operator*=(const TT &c)
		{
			x *= c;
			y *= c;
			return *this;
		}
		inline Vector2T operator/=(const TT &c)
		{
			x /= c;
			y /= c;
			return *this;
		}
		inline Vector2T operator+=(const Vector2T &c)
		{
			x += c.x;
			y += c.y;
			return *this;
		}
		inline Vector2T operator-=(const Vector2T &c)
		{
			x -= c.x;
			y -= c.y;
			return *this;
		}
		inline Vector2T operator*=(const Vector2T &c)
		{
			x *= c.x;
			y *= c.y;
			return *this;
		}
		inline Vector2T operator/=(const Vector2T &c)
		{
			x /= c.x;
			y /= c.y;
			return *this;
		}
		inline Vector2T operator=(const TT *p)
		{
			x = p[0];
			y = p[1];
			return *this;
		}
		inline Vector2T operator=(const Vector2T &v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		inline float normalise()
		{
			TT l;
			l = TT(sqrt(x*x + y*y));
			if (l != 0.0)
			{
				set(x / l, y / l);
			}
			else
			{
				set(0, 0);
			}
			return l;
		}

		friend inline Vector2T normalise(const Vector2T &v)
		{
			Vector2T temp(v);
			temp.normalise();
			return temp;
		}

		inline TT length() const
		{
			return sqrt(x*x + y*y);
		}

		friend inline TT length(const Vector2T &v)
		{
			return v.length();
		}

		inline TT lengthSquared() const
		{
			return x*x + y*y;
		}

		friend inline TT lengthSquared(const Vector2T &v)
		{
			return v.lengthSquared();
		}

		inline Vector2T clamp(float low, float high) const
		{
			Vector2T v(*this);
			if (v.x < low) v.x = low;
			if (v.x > high) v.x = high;
			if (v.y < low) v.y = low;
			if (v.y > high) v.y = high;
			return v;
		}

		friend inline TT clamp(const Vector2T &v, float low, float high)
		{
			return v.clamp(low, high);
		}

		inline Vector2T clamp(const Vector2T &low, const Vector2T &high) const
		{
			Vector2T v(*this);
			if (v.x < low.x) v.x = low.x;
			if (v.x > high.x) v.x = high.x;
			if (v.y < low.y) v.y = low.y;
			if (v.y > high.y) v.y = high.y;
			return v;
		}

		friend inline TT clamp(const Vector2T &v, const Vector2T &low, const Vector2T &high)
		{
			return v.clamp(low, high);
		}

		inline Vector2T saturate() const
		{
			return saturate((TT) 0, (TT) 1);
		}

		friend inline TT saturate(const Vector2T &v, float low, float high)
		{
			return v.saturate((TT) 0, (TT) 1);
		}

		inline Vector2T perpCW() const
		{
			return Vector2T(y,-x);
		}

		friend inline Vector2T perpCW(const Vector2T &v)
		{
			return v.perpCW();
		}

		inline Vector2T perpCCW() const
		{
			return Vector2T(-y, x);
		}

		friend inline Vector2T perpCCW(const Vector2T &v)
		{
			return v.perpCCW();
		}

		inline Vector2T reflect(const Vector2T &n) const
		{
			return (TT)2.0 * n * dot(n) - *this;
		}

		friend inline Vector2T reflect(const Vector2T &v, const Vector2T &n)
		{
			return v.reflect(n);
		}

		inline Vector2T dominantAxis() const
		{
			Vector2T v = abs();
			if (v.x >= v.y)
			{
				return x >= 0 ? UNIT_X() : NEGATIVE_UNIT_X();
			}
			else
			{
				return y >= 0 ? UNIT_Y() : NEGATIVE_UNIT_Y();
			}
		}

		friend inline Vector2T dominantAxis(const Vector2T &v)
		{
			return v.dominantAxis();
		}

		inline Vector2T swiz(Elements comp1, Elements comp2) const
		{
			return Vector2T(e[comp1], e[comp2]);
		}

		friend inline Vector2T swiz(const Vector2T &v, Elements comp1, Elements comp2)
		{
			return v.swiz(comp1, comp2);
		}

		inline void set(const Vector2T &value)
		{
			x = value.x;
			y = value.y;
		}

		inline void set(TT xy)
		{
			x = y = xy;
		}

		inline void set(TT xx, TT yy)
		{
			x = xx;
			y = yy;
		}

		template<typename T2>
		inline void set(const T2 *p)
		{
			x = TT(p[0]);
			y = TT(p[1]);
		}

		inline TT dot(const Vector2T &v) const
		{
			return x * v.x + y * v.y;
		}

		inline friend TT dot(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		inline TT cross(const Vector2T &v) const
		{
			return x * v.y - y * v.x;
		}

		inline friend TT cross(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		inline friend Vector2T operator*(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x*val, v.y*val);
		}

		inline friend Vector2T operator*(const TT &val, const Vector2T &v)
		{
			return Vector2T(val*v.x, val*v.y);
		}

		inline friend Vector2T operator*(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x*v2.x, v1.y*v2.y);
		}

		inline friend Vector2T operator+(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x + val, v.y + val);
		}

		inline friend Vector2T operator+(const TT &val, const Vector2T &v)
		{
			return Vector2T(val + v.x, val + v.y);
		}

		inline friend Vector2T operator+(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x + v2.x, v1.y + v2.y);
		}

		inline friend Vector2T operator-(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x - val, v.y - val);
		}

		inline friend Vector2T operator-(const TT &val, const Vector2T &v)
		{
			return Vector2T(val - v.x, val - v.y);
		}

		inline friend Vector2T operator-(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x - v2.x, v1.y - v2.y);
		}

		inline friend Vector2T operator/(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x / val, v.y / val);
		}

		inline friend Vector2T operator/(const TT &val, const Vector2T &v)
		{
			return Vector2T(val / v.x, val / v.y);
		}

		inline friend Vector2T operator/(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x / v2.x, v1.y / v2.y);
		}

		inline Vector2T &operator=(TT c)
		{
			x = c;
			y = c;
			return *this;
		}

		inline Vector2T &operator,(TT c)
		{
			y = c;
			return *this;
		}

		inline bool operator==(const Vector2T &v)
		{
			return (x == v.x) && (y == v.y);
		}

		inline bool operator<(const Vector2T &v)
		{
			return x < v.x;
		}

		inline Vector2T minimum(const Vector2T &v) const
		{
			return Vector2T((x<v.x ? x : v.x), (y<v.y ? y : v.y));
		}

		friend inline Vector2T minimum(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.minimum(v2);
		}

		inline Vector2T maximum(const Vector2T &v) const
		{
			return Vector2T((x>v.x ? x : v.x), (y>v.y ? y : v.y));
		}

		friend inline Vector2T maximum(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.maximum(v2);
		}

		inline TT dist(const Vector2T &v) const
		{
			return (v - *this).length();
		}

		friend inline TT dist(const Vector2T &v1, const Vector2T &v2)
		{
			return (v1 - v2).length();
		}

		inline Vector2T pow(const TT &e) const
		{
			return Vector2T(std::pow(x, e), std::pow(y, e));
		}

		friend inline Vector2T pow(const Vector2T &v, const TT &e)
		{
			return v.pow(e);
		}

		inline Vector2T log() const
		{
			return Vector2T(std::log(x), std::log(y));
		}

		friend inline Vector2T log(const Vector2T &v)
		{
			return v.log();
		}

		inline Vector2T exp(const Vector2T &v) const
		{
			return Vector2T(std::exp(x), std::exp(y));
		}

		friend inline Vector2T exp(const Vector2T &v)
		{
			return v.exp();
		}

		inline Vector2T abs() const
		{
			return Vector2T(std::fabs(x), std::fabs(y));
		}

		friend inline Vector2T abs(const Vector2T &v)
		{
			return v.abs();
		}

		inline Vector2T sign() const
		{
			return Vector2T(x>0 ? (TT)1.0 : (x<0 ? (TT) -1.0 : (TT)0.0), y>0 ? (TT)1.0 : (y<0 ? (TT) -1.0 : (TT)0.0));
		}

		friend inline Vector2T sign(const Vector2T &v)
		{
			return v.sign();
		}

		inline Vector2T rotate(TT angle) const
		{
			return Vector2T(x*cos(angle) - y*sin(angle), x*sin(angle) + y*cos(angle));
		}

		friend inline Vector2T rotate(const Vector2T &v, TT angle)
		{
			return v.rotate(angle);
		}




		#define KF_SWIZZLE2D(a,b) inline Vector2T a##b() { return Vector2T(a, b); }
		KF_SWIZZLE2D(x, x) KF_SWIZZLE2D(x, y) KF_SWIZZLE2D(y, x) KF_SWIZZLE2D(y, y) 
		KF_SWIZZLE2D(r, r) KF_SWIZZLE2D(r, g) KF_SWIZZLE2D(g, r) KF_SWIZZLE2D(g, g) 
		KF_SWIZZLE2D(s, s) KF_SWIZZLE2D(s, t) KF_SWIZZLE2D(t, s) KF_SWIZZLE2D(t, t)
		KF_SWIZZLE2D(u, u) KF_SWIZZLE2D(u, v) KF_SWIZZLE2D(v, u) KF_SWIZZLE2D(v, v)
		#undef KF_SWIZZLE2D

		inline static Vector2T ZERO()
		{
			return Vector2T(0, 0);
		}

		inline static Vector2T ONE()
		{
			return Vector2T(1, 1);
		}

		inline static Vector2T UNIT_X()
		{
			return Vector2T(1, 0);
		}

		inline static Vector2T UNIT_Y()
		{
			return Vector2T(0, 1);
		}

		inline static Vector2T NEGATIVE_UNIT_X()
		{
			return Vector2T(-1, 0);
		}

		inline static Vector2T NEGATIVE_UNIT_Y()
		{
			return Vector2T(0, -1);
		}
	};

	template <typename T1, typename T2>
	T1 convertVector2(const T2 &v)
	{
		T1 result;
		result.x = v.x;
		result.y = v.y;
		return result;
	}

	typedef Vector2T<float>  Vector2f;
	typedef Vector2T<double> Vector2d;
	typedef Vector2T<float>  Vector2;

}

#endif

