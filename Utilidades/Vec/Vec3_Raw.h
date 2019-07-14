#if !defined(_VEC3_H_)
#define _VEC3_H_

#if !defined(Assert)
#define Assert( _exp ) ((void)0)
#endif // #if !defined(Assert)

#if !defined(CHECK_VALID)
#define CHECK_VALID( _v)	Assert( (_v).isValid() )
#endif // #if !define(CHECK_VALID)


 
#if defined (__GNUC__) || defined (__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined (_MSC_VER)
#define FORCE_INLINE __forceinline 
#else
#define FORCE_INLINE inline
#endif

#include <iostream>
#include <cmath>


template <typename T>
class Vec3
{
public:
	T x, y, z;
	Vec3<T>(void);
    Vec3<T>(T i);
	Vec3<T>(T X, T Y, T Z);
	void Init(T ix = 0.f, T iy = 0.f, T iz = 0.f);
	T operator[](int i) const;
	T& operator[](int i);
	inline void Zero();
    Vec3<T> & operator++();
    Vec3<T> operator++(int);
	bool operator==(const Vec3<T>& v) const;
	bool operator!=(const Vec3<T>& v) const;
	FORCE_INLINE Vec3<T>&	operator+=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator-=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator*=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator*=(T s);
	FORCE_INLINE Vec3<T>&	operator/=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator/=(T s);
	FORCE_INLINE Vec3<T>&	operator+=(T fl);
	FORCE_INLINE Vec3<T>&	operator-=(T fl);
	FORCE_INLINE bool isValid() const;
	inline T	Length() const;
	FORCE_INLINE T LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y*y + z*z);
	}
	bool IsZero(T tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	void	NormalizeInPlace();
	FORCE_INLINE T	DistToSqr(const Vec3<T> &vOther) const;
	T	Dot(const Vec3<T>& vOther) const;
	T	Length2D(void) const;
	T	Length2DSqr(void) const;
	Vec3<T>& operator=(const Vec3<T> &vOther);
	Vec3<T>	operator+(const Vec3<T>& v) const;
	Vec3<T>	operator-(const Vec3<T>& v) const;
	Vec3<T>	operator*(const Vec3<T>& v) const;
	Vec3<T>	operator/(const Vec3<T>& v) const;
	Vec3<T>	operator*(T fl) const;
	Vec3<T>	operator/(T fl) const;

    friend std::ostream & operator<<(std::ostream &os, const Vec3<T>& v) 
    {
        return os << v.x << ' ' << v.y << ' ' << v.z;
	}
	
};

template <typename T>
inline bool Vec3<T>::isValid() const
{
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}


template <typename T>
inline void Vec3<T>::Init(T ix, T iy, T iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T i)
{
	x = y = z = i;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(void)
{
}

template <typename T>
inline void Vec3<T>::Zero()
{
	x = y = z = 0.f;
}

template <typename T>
inline void Clear(Vec3<T>& a)
{
	a.x = a.y = a.z = 0.f;
}

template <typename T>
inline Vec3<T> & Vec3<T>::operator++()
{
    x++;
    y++;
    z++;
    return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator++(int)
{
    Vec3<T> temp = *this;
    x++;
    y++;
    z++;
    return temp;
}

template <typename T>
inline Vec3<T>& Vec3<T>::operator=(const Vec3<T> &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

template <typename T>
inline T& Vec3<T>::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline T Vec3<T>::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

template <typename T>
FORCE_INLINE void Copy(const Vec3<T>& src, Vec3<T>& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(T fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator+=(T fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator-=(T fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.f && v.y != 0.f && v.z != 0.f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
inline T Vec3<T>::Length(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqsr = x*x + y*y + z*z;

	#if defined (__GNUC__) || defined (__clang__)
    __asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqsr));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}
	#elif
	return sqrt(sqsr);
	#endif

	return root;
}
 
template <typename T>
inline T Vec3<T>::Length2D(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqst = x*x + y*y;

	#if defined (__GNUC__) || defined (__clang__)
	__asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqst));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}
	#elif
	return sqrt(sqsr);
	#endif
 
	return root;
}
 
template <typename T>
inline T Vec3<T>::Length2DSqr(void) const
{
	return (x*x + y*y);
}
 
template <typename T>
inline Vec3<T> CrossProduct(const Vec3<T>& a, const Vec3<T>& b)
{
	return Vec3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
 
template <typename T>
T Vec3<T>::DistToSqr(const Vec3<T> &vOther) const
{
	Vec3<T> delta;
 
	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;
 
	return delta.LengthSqr();
}
 
template <typename T>
inline void Vec3<T>::NormalizeInPlace()
{
	Vec3<T>& v = *this;
 
	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON
 
	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
    
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(T fl) const
{
	Vec3<T> res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(T fl) const
{
	Vec3<T> res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

template <typename T>
inline T Vec3<T>::Dot(const Vec3<T>& vOther) const
{
	const Vec3<T>& a = *this;
 
	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

#endif //_VEC3_H_